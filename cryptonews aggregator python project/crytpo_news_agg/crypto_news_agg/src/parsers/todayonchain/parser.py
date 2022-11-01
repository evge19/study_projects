
from bs4 import BeautifulSoup
import typing as t 
from dateutil.parser import parse as date_parser
from crypto_news_agg.src.data.types import CryptoArticle
from crypto_news_agg.src.data.types import UrlParser

class TodayOnChain(UrlParser):
    url = "https://www.todayonchain.com/"

    @staticmethod
    def extract_news(soup) -> t.List[CryptoArticle]:
        articles_soup: BeautifulSoup = soup.find("div",attrs = {"id":"api-articles"})
        articles: t.List[BeautifulSoup] =articles_soup.findAll("a", attrs={"rel":"nofollow noopener noreferrer"})
        result = list()
        for article in articles:
            url  = article.get("href")
            article_info = article.find("div", class_="api_article_info")
            source = article_info.select("span.api_article_source")[0].text
            timestamp = date_parser(article_info.select("time.timeago")[0].get("datetime"))
            title = article.find("div", class_="api_article_title_sm").text
            result.append(CryptoArticle(url, title, source, timestamp))
        return result

    def start_extract_news(self):
        soup = self.get(self.url)
        result = self.extract_news(soup)
        #TODO send result to database
        return result