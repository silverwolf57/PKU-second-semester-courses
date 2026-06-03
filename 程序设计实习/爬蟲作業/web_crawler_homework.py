import requests
from bs4 import BeautifulSoup
import os

'''获取url'''
def get_html(url):
    headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) ""AppleWebKit/537.36 (KHTML, like Gecko) ""Chrome/120.0.0.0 Safari/537.36","Accept-Language": "zh-CN,zh;q=0.9"}
    try:
        response = requests.get(url,headers=headers,timeout=10)
        response.raise_for_status()
        response.encoding = response.apparent_encoding
        return response.text
    except Exception as e:
        print("获取网页失败：", e)
        return ""

'''抓取近义词和图片链接'''
def get_synonyms_and_image(word):
    url = f"https://cn.bing.com/dict/search?q={word}"
    html = get_html(url)
    if not html:
        return [], None
    soup = BeautifulSoup(html, "html.parser")
    synonyms = []
    #直接根据近义词的html进行解析
    synonym_box = soup.find("div", id="synoid")
    if synonym_box:
        synonym_spans = synonym_box.find_all("span",class_="b_alink")
        synonyms = [span.get_text(strip=True) for span in synonym_spans]
    img_url = None
    img_area = soup.find("div", class_="img_area")
    if img_area:
        img_tag = img_area.find(
            "img",
            class_="rms_img"
        )
        if img_tag:
            img_url = img_tag.get("src")
    return synonyms, img_url

'''下载图片 '''
def save_image(word, img_url):
    if not img_url:
        return
    try:
        headers = {"User-Agent":"Mozilla/5.0"}
        response = requests.get(img_url,headers=headers,timeout=10)
        current_dir = os.path.dirname(os.path.abspath(__file__))
        image_path = os.path.join(current_dir,f"{word}.png")
        with open(image_path, "wb") as f:
            f.write(response.content)
        print(f"图片保存成功：{word}.png")
    except Exception as e:
        print(f"{word} 图片下载失败：{e}")

def main():
    current_dir = os.path.dirname(os.path.abspath(__file__))
    words_path = os.path.join( current_dir,"words.txt")
    result_path = os.path.join(current_dir,"result.txt")
    if not os.path.exists(words_path):
        print("未找到 words.txt")
        return
    #从word.txt中读取单词并进行查找
    with open(words_path,"r",encoding="utf-8") as f:
        words = [line.strip() for line in f if line.strip()]
    with open(result_path,"w",encoding="utf-8") as result_file:
        for word in words:
            print(f"正在处理: {word}")
            synonyms, img_url = get_synonyms_and_image(word)
            #若是同义词则写入result.txt,有图片就下载
            if synonyms:
                result_file.write(f"${word}\n")
                for s in synonyms:
                    result_file.write(s + "\n")
            if img_url:
                save_image(word, img_url)
    print("全部完成！")

if __name__ == "__main__":
    main()