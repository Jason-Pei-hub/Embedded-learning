import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt, QObject, pyqtSignal, QThread
import time
import logging
import speech_recognition as sr
from aip import AipSpeech

logging.basicConfig(level=logging.DEBUG)

BAIDU_APP_ID = '84536213'
BAIDU_API_KEY = 'JRWrs67HfGZZ94PojymbsCpT'
BAIDU_SECRET_KEY = '9AlkJHrWgOFYamo5jQRcrOrrUzTggfhZ'
aip_speech = AipSpeech(BAIDU_APP_ID, BAIDU_API_KEY, BAIDU_SECRET_KEY)

class RecognitionWorker(QObject):
    finished = pyqtSignal()
    recognized = pyqtSignal(str)

    def __init__(self):
        super().__init__()

        self.r = sr.Recognizer()
        self.mic = sr.Microphone(sample_rate=16000)

    def run(self):
        while True:
            logging.info('录音中...')
            with self.mic as source:
                self.r.adjust_for_ambient_noise(source)
                audio = self.r.listen(source)

            logging.info('录音结束，识别中...')
            start_time = time.time()

            # 识别音频数据
            ret = aip_speech.asr(audio.get_wav_data(), 'wav', 16000, {'dev_pid': 1537})

            if ret and ret['err_no'] == 0:
                result = ret['result'][0]
                logging.info(f'识别结果：{result}')
                end_time = time.time()
                logging.info(f'识别耗时：{end_time - start_time}秒')
                self.recognized.emit(result)
            else:
                logging.error(f'识别错误：{ret["err_msg"]}')
                self.recognized.emit('识别错误')

            time.sleep(1)

    def stop(self):
        self.finished.emit()

class RecognitionWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setWindowTitle('语音识别')
        self.setGeometry(100, 100, 600, 400)
        self.setStyleSheet("background-color: black;")

        self.label = QLabel(self)
        self.label.setAlignment(Qt.AlignCenter)
        self.label.setStyleSheet("color: white;")
        font = QFont()
        font.setPointSize(24)
        self.label.setFont(font)

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)

        self.worker = RecognitionWorker()
        self.worker_thread = QThread()
        self.worker.moveToThread(self.worker_thread)

        self.worker.recognized.connect(self.updateLabel)
        self.worker.finished.connect(self.worker_thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.worker_thread.finished.connect(self.worker_thread.deleteLater)

        self.worker_thread.started.connect(self.worker.run)
        self.worker_thread.start()

    def updateLabel(self, text):
        self.label.setText(text)

    def closeEvent(self, event):
        self.worker.stop()
        super().closeEvent(event)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = RecognitionWindow()
    window.show()
    sys.exit(app.exec_())
