import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton, QVBoxLayout, QHBoxLayout, QSpinBox, QMessageBox, QTextEdit, QGridLayout
from PyQt5.QtCore import QThread, pyqtSignal
from selenium import webdriver
import time
from selenium.webdriver.common.by import By
import difflib  # 用于文本相似度比较
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import NoSuchElementException, TimeoutException
import random
from PyQt5.QtGui import QIcon,QFont
from selenium.common.exceptions import NoSuchElementException

class Worker(QThread):
    output_signal = pyqtSignal(str)

    def __init__(self, account, password, level_number, desired_score, accuracy_rate, min_time_per_question, max_time_per_question):
        super().__init__()
        self.account = account
        self.password = password
        self.level_number = level_number
        self.desired_score = desired_score
        self.accuracy_rate = accuracy_rate
        self.min_time_per_question = min_time_per_question
        self.max_time_per_question = max_time_per_question





    def run(self):
        self.accuracy_rate = self.accuracy_rate - 80
        self.accuracy_rate = self.accuracy_rate * 5

        self.output_signal.emit("好的，正在开始答题......\n")

        driver = webdriver.Chrome(executable_path='data/chromedriver.exe')
        driver.get('http://www.ytosclb.cn/index.php?m=home&c=auth&a=login')


        # 登录流程
        driver.maximize_window()
        driver.implicitly_wait(10)
        input_box = driver.find_element(By.CSS_SELECTOR, "input[type='text']")
        input_box.send_keys(self.account)
        input_box = driver.find_element(By.CSS_SELECTOR, "input[type='password']")
        input_box.send_keys(self.password)
        button = driver.find_element(By.XPATH, "//button[text()='登录']")
        button.click()

        # 进入练习页面
        driver.find_element(By.LINK_TEXT, "网上练兵").click()
        driver.find_element(By.LINK_TEXT, "闯关练兵").click()

        file_path_questions = 'data/question.txt'  # 存储问题的文件路径
        file_path_answers = 'data/data.txt'  # 存储答案的文件路径

        question_map = {}
        with open(file_path_questions, 'r', encoding='utf-8') as file:
            for line in file:
                line = line.strip()
                if '=' in line:
                    question_id, question_text = line.split('=', 1)
                    question_map[question_id] = question_text

        answer_map = {}
        with open(file_path_answers, 'r', encoding='utf-8') as file:
            for line in file:
                line = line.strip()
                if '=' in line:
                    question_id, answer = line.split('=', 1)
                    answer_map[question_id] = answer

        current_score = 0
        total_questions = 0
        correct_questions = 0

        while True:
            driver.find_element(By.LINK_TEXT, "拖拉机装配工").click()
            driver.find_element(By.LINK_TEXT, self.level_number).click()


            current_loop_correct_questions = 0
            current_loop_total_questions = 0

            while True:
                elements = driver.find_elements(By.CLASS_NAME, "hui14.exambt.ng-binding")

                for element in elements:
                    text = element.text[3:]
                    best_match = difflib.get_close_matches(text, question_map.values(), n=1, cutoff=0.5)
                    if best_match:
                        question_id = [k for k, v in question_map.items() if v == best_match[0]][0]
                        if question_id in answer_map:
                            current_loop_total_questions += 1
                            total_questions += 1
                            answer = answer_map[question_id]

                            current_loop_accuracy = (
                                        current_loop_correct_questions / current_loop_total_questions * 100) if current_loop_total_questions > 0 else 0
                            correct_this_question = True if current_loop_accuracy < 90 else (
                                        random.randint(0, 99) < self.accuracy_rate)

                            if ',' in answer:
                                question_type = '多选题'
                                answer_ids = answer.split(',')
                                if not correct_this_question:
                                    answer_ids = answer_ids[:1]
                                for answer_id in answer_ids:
                                    driver.find_element(By.CSS_SELECTOR, f'[id="{answer_id.lower()}"]').click()
                            elif answer.lower() in ['t', 'f']:
                                question_type = '判断题'
                                if not correct_this_question:
                                    answer = 't' if answer.lower() == 'f' else 'f'
                                driver.find_element(By.CSS_SELECTOR, f'[id="{answer.lower()}"]').click()
                            else:
                                question_type = '单选题'
                                if not correct_this_question:
                                    answer = 'a' if answer.lower() != 'a' else 'b'
                                driver.find_element(By.CSS_SELECTOR, f'[id="{answer.lower()}"]').click()

                            if correct_this_question:
                                current_loop_correct_questions += 1
                                correct_questions += 1
                                current_score += 1

                            self.output_signal.emit(f'题目编号: {question_id}, 类型: {question_type}, 答案: {answer}\n')
                            time.sleep(random.randint(self.min_time_per_question, self.max_time_per_question))

                            driver.find_element(By.XPATH, "//button[text()='提交答案']").click()
                        else:
                            self.output_signal.emit(f'未找到题目编号 {question_id} 的答案\n')


                    else:
                        self.output_signal.emit(f'未找到题目文本对应的题目编号: {text}\n')
                        # 通过ID判断题目类型并选择选项
                        try:
                            driver.find_element(By.ID, 'a')
                            # 单选题或多选题选择选项 A
                            driver.find_element(By.CSS_SELECTOR, '[id="a"]').click()
                        except NoSuchElementException:
                            # 判断题选择选项 F
                            driver.find_element(By.CSS_SELECTOR, '[id="f"]').click()
                        driver.find_element(By.XPATH, "//button[text()='提交答案']").click()

                self.output_signal.emit(f"总答题数: {total_questions}, 错误题目数: {total_questions - correct_questions}, 目前得分: {current_score}\n")
                self.output_signal.emit('\n')

                try:
                    WebDriverWait(driver, 3).until(EC.alert_is_present())
                    alert = driver.switch_to.alert
                    alert.accept()
                    break
                except TimeoutException:
                    pass

            if current_score >= self.desired_score:
                self.output_signal.emit(f'恭喜！您已经获得了{current_score}分，达到了目标分数。\n')
                break

            driver.find_element(By.LINK_TEXT, "继续闯关").click()

        driver.quit()

class MainWindow(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setStyleSheet("background-color: white;")
        self.setWindowIcon(QIcon('data/echo.ico'))

        label4 = QLabel('输入您的账号密码')
        label4.setStyleSheet("color: #316396; font-family: Microsoft YaHei; font-size: 9pt;")

        account_label = QLabel('账号:')
        account_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        password_label = QLabel('密码:')
        password_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        label3 = QLabel('仅有目前能做的最大关卡得分才能生效')
        label3.setStyleSheet("color: #316396; font-family: Microsoft YaHei; font-size: 9pt;")

        level_number_label = QLabel('关卡编号:')
        level_number_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        desired_score_label = QLabel('目标分数:')
        desired_score_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        label1 = QLabel('准确率软件已经设定在80%以上')
        label1.setStyleSheet("color: #316396; font-family: Microsoft YaHei; font-size: 9pt;")

        accuracy_rate_label = QLabel('答题准确率:')
        accuracy_rate_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        label2 = QLabel('答题时间软件会根据您填写的最小值和最大值取平均数决定')
        label2.setStyleSheet("color: #316396; font-family: Microsoft YaHei; font-size: 9pt;")

        min_time_per_question_label = QLabel('答题时间最小值:')
        min_time_per_question_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        max_time_per_question_label = QLabel('答题时间最大值:')
        max_time_per_question_label.setStyleSheet("font-family: Microsoft YaHei; font-size: 11pt;")

        self.account_edit = QLineEdit()
        self.account_edit.setFont(QFont("Microsoft YaHei", 11))  # 设置账号输入框的字体为微软雅黑，字号为11pt

        self.password_edit = QLineEdit()
        self.password_edit.setFont(QFont("Microsoft YaHei", 11))  # 设置密码输入框的字体为微软雅黑，字号为11pt
        self.password_edit.setEchoMode(QLineEdit.Password)  # 设置密码输入框为密码模式

        self.level_number_edit = QLineEdit()
        self.level_number_edit.setFont(QFont("Microsoft YaHei", 11))  # 设置关卡编号输入框的字体为微软雅黑，字号为11pt

        self.desired_score_spinbox = QSpinBox()
        self.desired_score_spinbox.setFont(QFont("Microsoft YaHei", 11))  # 设置目标分数Spin Box的字体为微软雅黑，字号为11pt
        self.desired_score_spinbox.setMinimum(0)  # 设置最小值为0
        self.desired_score_spinbox.setMaximum(999999)  # 设置最大值为9999

        self.accuracy_rate_spinbox = QSpinBox()
        self.accuracy_rate_spinbox.setFont(QFont("Microsoft YaHei", 11))  # 设置答题准确率Spin Box的字体为微软雅黑，字号为11pt

        self.min_time_per_question_spinbox = QSpinBox()
        self.min_time_per_question_spinbox.setFont(QFont("Microsoft YaHei", 11))  # 设置答题时间最小值Spin Box的字体为微软雅黑，字号为11pt

        self.max_time_per_question_spinbox = QSpinBox()
        self.max_time_per_question_spinbox.setFont(QFont("Microsoft YaHei", 11))  # 设置答题时间最大值Spin Box的字体为微软雅黑，字号为11pt

        # self.password_edit.setEchoMode(QLineEdit.Password)

        self.run_button = QPushButton('开始闯关')
        self.run_button.setFixedHeight(40)  # 设置按钮高度为 40 像素
        self.run_button.setStyleSheet("background-color: #316396; color: white; border-radius: 20px;font-family: Microsoft YaHei")
        self.run_button.clicked.connect(self.run)  # 确保已定义 self.run 方法

        # 使用表格布局
        grid = QGridLayout()
        grid.setSpacing(10)  # 设置间距为 10 像素

        widgets = [
            (label4, None),
            (account_label, self.account_edit),
            (password_label, self.password_edit),
            (label3, None),
            (level_number_label, self.level_number_edit),
            (desired_score_label, self.desired_score_spinbox),
            (label1, None),
            (accuracy_rate_label, self.accuracy_rate_spinbox),
            (label2, None),
            (min_time_per_question_label, self.min_time_per_question_spinbox),
            (max_time_per_question_label, self.max_time_per_question_spinbox),
        ]

        for i, (label_widget, input_widget) in enumerate(widgets):
            grid.addWidget(label_widget, i, 0)
            if input_widget:
                grid.addWidget(input_widget, i, 1)

        # 设置主布局
        mainLayout = QVBoxLayout()
        mainLayout.addLayout(grid)
        mainLayout.addWidget(self.run_button)
        mainLayout.setSpacing(20)  # 设置布局内部小部件之间的间距为 20 像素

        self.output_textedit = QTextEdit()
        self.output_textedit.setReadOnly(True)
        mainLayout.addWidget(self.output_textedit)

        self.setLayout(mainLayout)
        self.setWindowTitle('一拖自动答题——J.Pei')
        self.setGeometry(300, 300, 500, 600)  # 设置窗口初始位置和大小
        self.show()


    def print_output(self, text):
        self.output_textedit.append(text)  # 在文本框中追加输出内容

    def run(self):
        account = self.account_edit.text()
        password = self.password_edit.text()
        level_number = self.level_number_edit.text()
        desired_score = self.desired_score_spinbox.value()
        accuracy_rate = self.accuracy_rate_spinbox.value()
        min_time_per_question = self.min_time_per_question_spinbox.value()
        max_time_per_question = self.max_time_per_question_spinbox.value()

        self.worker = Worker(account, password, level_number, desired_score, accuracy_rate, min_time_per_question, max_time_per_question)
        self.worker.output_signal.connect(self.print_output)
        self.worker.start()


if __name__ == '__main__':

    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())
