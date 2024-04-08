from selenium import webdriver
import time
from selenium.webdriver.common.by import By
import difflib  # 用于文本相似度比较
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import NoSuchElementException, TimeoutException
import random

# 用户输入部分
file_path_questions = 'question.txt'  # 存储问题的文件路径
file_path_answers = 'data.txt'  # 存储答案的文件路径
account = input("请输入账号: ")  # 用户账号
password = input("请输入密码: ")  # 用户密码
level_number = input("请输入要闯关的关卡编号: ")  # 指定要闯的关卡编号
desired_score = int(input("请输入您想要获得的分数: "))  # 用户期望的分数
print("请您输入您期待的正确率，我会尽量按照您的要求控制正确率，但是正确率将不会低于80%")
accuracy_rate = int(input("请输入您想要的答题准确率（80-100）: "))  # 用户设定的答题准确率
print("接下来请您输入作答时间的区间，我会在区间内随机时间长度帮您作答")
min_time_per_question = int(input("请输入您希望每道题需要时间的最小值（秒）: "))  # 每题最短答题时间
max_time_per_question = int(input("请输入您希望每道题需要时间的最大值（秒）: "))  # 每题最长答题时间
print("好的，正在开始答题......")
print()
# 初始化Selenium WebDriver并打开指定网页
driver = webdriver.Edge(executable_path='MicrosoftWebDriver.exe')
driver.get('http://www.ytosclb.cn/index.php?m=home&c=auth&a=login')
time.sleep(2)

accuracy_rate = accuracy_rate-80
accuracy_rate = accuracy_rate*5

# 登录流程
driver.maximize_window()
driver.implicitly_wait(10)
input_box = driver.find_element(By.CSS_SELECTOR, "input[type='text']")
input_box.send_keys(account)
input_box = driver.find_element(By.CSS_SELECTOR, "input[type='password']")
input_box.send_keys(password)
button = driver.find_element(By.XPATH, "//button[text()='登录']")
button.click()

# 进入练习页面
driver.find_element(By.LINK_TEXT, "网上练兵").click()
driver.find_element(By.LINK_TEXT, "闯关练兵").click()

# 初始化分数和题目计数器
current_score = 0
total_questions = 0
correct_questions = 0

# 读取问题和答案文件，创建映射
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

while True:


    # 选择关卡并开始闯关
    driver.find_element(By.LINK_TEXT, "拖拉机装配工").click()
    driver.find_element(By.LINK_TEXT, level_number).click()
    time.sleep(2)  # 等待页面加载

    current_loop_correct_questions = 0
    current_loop_total_questions = 0

    while True:
        elements = driver.find_elements(By.CLASS_NAME, "hui14.exambt.ng-binding")

        for element in elements:
            text = element.text[3:]
            best_match = difflib.get_close_matches(text, question_map.values(), n=1, cutoff=0.6)
            if best_match:
                question_id = [k for k, v in question_map.items() if v == best_match[0]][0]
                if question_id in answer_map:
                    current_loop_total_questions += 1
                    total_questions += 1
                    answer = answer_map[question_id]

                    current_loop_accuracy = (current_loop_correct_questions / current_loop_total_questions * 100) if current_loop_total_questions > 0 else 0
                    correct_this_question = True if current_loop_accuracy < 80 else (random.randint(0, 99) < accuracy_rate)

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

                    print(f'题目编号: {question_id}, 类型: {question_type}, 答案: {answer}')
                    time.sleep(random.randint(min_time_per_question, max_time_per_question))

                    driver.find_element(By.XPATH, "//button[text()='提交答案']").click()
                else:
                    print(f'未找到题目编号 {question_id} 的答案')
            else:
                print(f'未找到题目文本对应的题目编号: {text}')

        print(f"本次闯关总答题数: {current_loop_total_questions}, 错误题目数: {current_loop_total_questions - current_loop_correct_questions}, 本次闯关正确率: {current_loop_correct_questions / current_loop_total_questions * 100:.2f}%")
        print(f"总答题数: {total_questions}, 错误题目数: {total_questions - correct_questions}, 总正确率: {correct_questions / total_questions * 100:.2f}%, 目前得分: {current_score}")
        print()
        try:
            WebDriverWait(driver, 3).until(EC.alert_is_present())
            alert = driver.switch_to.alert
            alert.accept()
            break
        except TimeoutException:
            pass

    # 检查是否达到期望分数
    if current_score >= desired_score:
        print(f"恭喜！您已经获得了{current_score}分，达到了目标分数。")
        break

    driver.find_element(By.LINK_TEXT, "继续闯关").click()


driver.quit()
