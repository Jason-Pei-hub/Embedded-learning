import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtGui import QFont, QColor
from PyQt5.QtCore import Qt, pyqtSignal, QObject
import threading
import websocket
import time
import uuid
import json
import logging
import const
import pyaudio


class RealtimeASRWorker(QObject):
    recognition_result = pyqtSignal(str)

    def __init__(self):
        super().__init__()

    def initASR(self):
        self.CHUNK = 1024
        self.FORMAT = pyaudio.paInt16
        self.CHANNELS = 1
        self.RATE = 16000
        self.RECORD_SECONDS = 5

        logger = logging.getLogger()

        def send_start_params(ws):
            req = {
                "type": "START",
                "data": {
                    "appid": const.APPID,
                    "appkey": const.APPKEY,
                    "dev_pid": const.DEV_PID,
                    "cuid": "yourself_defined_user_id",
                    "sample": self.RATE,
                    "format": "pcm"
                }
            }
            body = json.dumps(req)
            ws.send(body, websocket.ABNF.OPCODE_TEXT)
            logger.info("send START frame with params:" + body)

        def send_audio(ws):
            p = pyaudio.PyAudio()
            stream = p.open(format=self.FORMAT,
                            channels=self.CHANNELS,
                            rate=self.RATE,
                            input=True,
                            frames_per_buffer=self.CHUNK)

            logger.info("开始录音...")

            while True:
                data = stream.read(self.CHUNK)
                ws.send(data, websocket.ABNF.OPCODE_BINARY)

            stream.stop_stream()
            stream.close()
            p.terminate()

        def send_finish(ws):
            req = {
                "type": "FINISH"
            }
            body = json.dumps(req)
            ws.send(body, websocket.ABNF.OPCODE_TEXT)
            logger.info("send FINISH frame")

        def on_open(ws):
            def run(*args):
                send_start_params(ws)
                send_audio(ws)
                send_finish(ws)
                logger.debug("thread terminating")

            threading.Thread(target=run).start()

        def on_message(ws, message):
            logger.info("Response: " + message)
            response = json.loads(message)
            if "result" in response:
                result = response["result"]
                self.recognition_result.emit(result)

        def on_error(ws, error):
            logger.error("error: " + str(error))

        def on_close(ws):
            logger.info("ws close ...")

        self.logger = logger
        logging.basicConfig(format='[%(asctime)-15s] [%(funcName)s()][%(levelname)s] %(message)s')
        self.logger.setLevel(logging.DEBUG)
        self.logger.info("begin")

        uri = const.URI + "?sn=" + str(uuid.uuid1())
        self.logger.info("uri is " + uri)
        ws_app = websocket.WebSocketApp(uri,
                                        on_open=on_open,
                                        on_message=on_message,
                                        on_error=on_error,
                                        on_close=on_close)
        ws_app.run_forever()


class RealtimeASR(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.initASRWorker()

    def initUI(self):
        self.setWindowTitle("Realtime ASR")
        self.setGeometry(100, 100, 400, 200)
        self.setStyleSheet("background-color: black;")

        self.text_label = QLabel(self)
        self.text_label.setAlignment(Qt.AlignCenter)
        self.text_label.setStyleSheet("color: white;")
        self.text_label.setFont(QFont("Arial", 24))

        self.resize(1000, 600)

        layout = QVBoxLayout()
        layout.addWidget(self.text_label)
        self.setLayout(layout)

    def initASRWorker(self):
        self.worker = RealtimeASRWorker()
        self.worker.recognition_result.connect(self.update_text)

        threading.Thread(target=self.worker.initASR).start()

    def update_text(self, text):
        self.text_label.setText(text)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = RealtimeASR()
    window.show()
    sys.exit(app.exec_())