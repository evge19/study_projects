import requests
from bs4 import BeautifulSoup

def get_web_page(url):
    with requests.session() as session:
        resp = session.get(url)
        if resp.status_code != 200:
            print("there is an error!")
            print(resp)
        return BeautifulSoup(resp.text)