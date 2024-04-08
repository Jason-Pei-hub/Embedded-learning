def read_answers_from_file(file_path):
    """
    从文件中读取答案并存储在字典中。
    """
    answers = {}
    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            if '=' in line:
                key, value = line.strip().split('=', 1)
                answers[key] = value
    return answers


def get_answer_by_id(answers, question_id):
    """
    根据题目编号获取答案，并判断题目类型。
    """
    question_id_str = str(question_id)
    if question_id_str in answers:
        answer = answers[question_id_str]
        # 判断题目类型
        if ',' in answer:
            print(f"题目编号{question_id}的答案是: {answer} (多选题)")
        elif answer.lower() in ['t', 'f']:
            print(f"题目编号{question_id}的答案是: {answer} (判断题)")
        else:
            print(f"题目编号{question_id}的答案是: {answer} (单选题)")
    else:
        print(f"未找到题目编号{question_id}的答案")


if __name__ == "__main__":
    # 替换为你的文件路径
    file_path = 'data.txt'

    # 从文件中读取答案
    answers = read_answers_from_file(file_path)

    # 请求用户输入题目编号
    question_id = input("请输入题目编号: ")

    # 获取并打印答案及题目类型
    get_answer_by_id(answers, question_id)
