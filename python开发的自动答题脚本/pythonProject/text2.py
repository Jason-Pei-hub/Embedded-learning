import requests
import json

# 目标URL
url = "http://example.com/index.php?m=home&c=break&a=ajaxquestion&passid=262&mod=L1"

# 发送GET请求
response = requests.get(url)

# 检查请求是否成功
if response.status_code == 200:
    # 解析JSON数据
    data = response.json()

    # 美化打印JSON数据
    print(json.dumps(data, indent=4, ensure_ascii=False))
else:
    print(f'请求失败，状态码：{response.status_code}')
