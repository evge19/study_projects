import pandas
import requests
from datetime import datetime
import typing as t 
from dateutil.parser import parse as date_parser
from dateutil import parser

import sqlite3

headers = {
    'authority': 'conpletus.cointelegraph.com',
    'sec-ch-ua': '" Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"',
    'accept': '*/*',
    'content-type':'application/json',
    'sec-ch-ua-mobile':'?0',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.45 Safari/537.36',
    'sec-ch-ua-platform': '"Windows"',
    'origin': 'https://cointelegraph.com',
    'sec-fetch-site': 'same-site',
    'sec-fetch-mode':'cors',
    'sec-fetch-dest':'empty',
    'referer':'https://cointelegraph.com/',
    'accept-language':'ru,en-US;q=0.9,en;q=0.8'
}

start_note = 1

r = requests.post('https://conpletus.cointelegraph.com/v1/',
                  headers=headers,
                  data='{"operationName":"MainPagePostsQuery","variables":{"place":"index","offset":' + str(start_note) +',"length":10,"short":"en","cacheTimeInMS":1000},"query":"query MainPagePostsQuery($short: String, $offset: Int\u0021, $length: Int\u0021, $place: String = \\"index\\") {\\n  locale(short: $short) {\\n    posts(order: \\"postPublishedTime\\", offset: $offset, length: $length, place: $place) {\\n      data {\\n        cacheKey\\n        id\\n        slug\\n        postTranslate {\\n          cacheKey\\n          id\\n          title\\n          avatar\\n          published\\n          publishedHumanFormat\\n          leadText\\n          __typename\\n        }\\n        category {\\n          cacheKey\\n          id\\n          slug\\n          categoryTranslates {\\n            cacheKey\\n            id\\n            title\\n            __typename\\n          }\\n          __typename\\n        }\\n        author {\\n          cacheKey\\n          id\\n          slug\\n          authorTranslates {\\n            cacheKey\\n            id\\n            name\\n            __typename\\n          }\\n          __typename\\n        }\\n        postBadge {\\n          cacheKey\\n          id\\n          label\\n          postBadgeTranslates {\\n            cacheKey\\n            id\\n            title\\n            __typename\\n          }\\n          __typename\\n        }\\n        __typename\\n      }\\n      postsCount\\n      hasMorePosts\\n      __typename\\n    }\\n    __typename\\n  }\\n}\\n"}'
                 )
r.json()
df = pandas.json_normalize(r.json()['data']['locale']['posts']['data'])
#print(df['postTranslate.title'][0])
result = []
for el in range(len(df)):
    title=df['postTranslate.title'][el]
    url=f'https://cointelegraph.com/news/{df["slug"][el]}'
    source='CoinTelegraph'
    timestamp=str(parser.parse(df['postTranslate.published'][el]))
    text=''
    result.append([url, title, source, timestamp,text])
#print(result)


try:
    sqlite_connection = sqlite3.connect('../crytpo_news_agg/cryptonews.db')
    cursor = sqlite_connection.cursor()
    
    for el in range(len(result)):
        cursor.execute("select * from Articles")
        rows = cursor.fetchall()
        sqlite_insert_query="INSERT INTO Articles (id, url, title, source, timestamp, text) VALUES ("+str(len(rows))+", '" + result[el][0] +"', '"+result[el][1] +"', '"+result[el][2]+"', '"+result[el][3]+"', '"+result[el][4]+"');"
        count = cursor.execute(sqlite_insert_query)
        sqlite_connection.commit()
    cursor.close()

except sqlite3.Error as error:
    print("Error to connect to sqlite", error)
finally:
    if sqlite_connection:
        sqlite_connection.close()

