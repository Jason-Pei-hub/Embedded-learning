# -*- encoding:utf-8 -*-
import hashlib
import hmac
import base64
import json
import time
import threading
import pyaudio
from websocket import create_connection
import websocket
from urllib.parse import quote
import logging
from PyQt5.QtWidgets import QApplication, QLabel, QWidget, QVBoxLayout
from PyQt5.QtCore import Qt, pyqtSignal, QObject
from PyQt5.QtGui import QFont
import sys


class Communicate(QObject):
    update_label = pyqtSignal(str)


class Client(threading.Thread):
    def __init__(self, comm):
        threading.Thread.__init__(self)
        self.comm = comm
        self.base_url = "ws://rtasr.xfyun.cn/v1/ws"
        self.app_id = "3e37394f"
        self.api_key = "38a04285197d14e35db52dc46dce29ed"
        self.end_tag = "{\"end\": true}"

        ts = str(int(time.time()))
        tt = (self.app_id + ts).encode('utf-8')
        md5 = hashlib.md5()
        md5.update(tt)
        baseString = md5.hexdigest()
        baseString = bytes(baseString, encoding='utf-8')

        apiKey = self.api_key.encode('utf-8')
        signa = hmac.new(apiKey, baseString, hashlib.sha1).digest()
        signa = base64.b64encode(signa)
        signa = str(signa, 'utf-8')

        self.ws = create_connection(self.base_url + "?appid=" + self.app_id + "&ts=" + ts + "&signa=" + quote(signa))
        self.trecv = threading.Thread(target=self.recv)
        self.trecv.start()

        self.audio_stream = None
        self.audio_format = pyaudio.paInt16  # 16-bit PCM
        self.audio_chunk = 1280  # Chunk size in bytes
        self.audio_channels = 1  # Mono
        self.audio_rate = 16000  # Sample rate

    def run(self):
        self.send_audio_stream()

    def send_audio_stream(self):
        p = pyaudio.PyAudio()
        self.audio_stream = p.open(format=self.audio_format,
                                   channels=self.audio_channels,
                                   rate=self.audio_rate,
                                   input=True,
                                   frames_per_buffer=self.audio_chunk)

        try:
            while True:
                audio_data = self.audio_stream.read(self.audio_chunk)
                self.ws.send(audio_data)
                time.sleep(0.04)  # Adjust delay as needed
        except KeyboardInterrupt:
            pass
        finally:
            if self.audio_stream is not None:
                self.audio_stream.stop_stream()
                self.audio_stream.close()

            p.terminate()

        self.ws.send(bytes(self.end_tag.encode('utf-8')))
        print("send end tag success")

    def recv(self):
        try:
            while self.ws.connected:
                result = str(self.ws.recv())
                if len(result) == 0:
                    print("receive result end")
                    break
                result_dict = json.loads(result)

                if result_dict["action"] == "started":
                    print("Handshake success, result: " + result)

                if result_dict["action"] == "result":
                    print("rtasr result: " + result_dict["data"])
                    text = self.extract_text(result_dict["data"])
                    self.comm.update_label.emit(text)

                if result_dict["action"] == "error":
                    print("rtasr error: " + result)
                    self.ws.close()
                    return
        except websocket.WebSocketConnectionClosedException:
            print("Receive result end")

    @staticmethod
    def extract_text(data):
        text = ''
        try:
            data_json = json.loads(data)
            for rt in data_json['cn']['st']['rt']:
                for ws in rt['ws']:
                    for cw in ws['cw']:
                        text += cw['w']
        except Exception as e:
            print(f"Error extracting text: {e}")
        return text

    def close(self):
        self.ws.close()
        print("Connection closed")


class DisplayWindow(QWidget):
    def __init__(self, comm):
        super().__init__()
        self.initUI()
        comm.update_label.connect(self.update_text)

    def initUI(self):
        self.setWindowTitle('ASR Display')
        self.setGeometry(100, 100, 800, 600)
        self.setStyleSheet("background-color: black;")

        self.label = QLabel('', self)
        self.label.setAlignment(Qt.AlignCenter)
        self.label.setStyleSheet("color: white;")
        self.label.setFont(QFont('Arial', 24))

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)

    def update_text(self, text):
        self.label.setText(text)


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)

    app = QApplication(sys.argv)

    comm = Communicate()
    window = DisplayWindow(comm)
    window.show()

    client = Client(comm)
    client.start()

    sys.exit(app.exec_())
