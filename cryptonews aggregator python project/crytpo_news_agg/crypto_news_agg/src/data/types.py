import requests
from bs4 import BeautifulSoup
from datetime import datetime

class UrlParser:
    def get(self, url, parser="html.parser", **kwargs)-> BeautifulSoup:
        with requests.session() as session:
            html_doc = session.get(url,**kwargs)
        return BeautifulSoup(html_doc.content, parser)


from dataclasses import dataclass

@dataclass
class CryptoArticle:
    url: str
    title: str
    source: str
    timestamp: datetime
    text: str = None
