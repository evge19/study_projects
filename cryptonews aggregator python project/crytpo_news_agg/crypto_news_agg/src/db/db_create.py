import sqlite3

try:
    sqlite_connection = sqlite3.connect('cryptonews.db')
    sqlite_create_table_query = '''CREATE TABLE Articles (
                                id INTEGER PRIMARY KEY,
                                url TEXT NOT NULL,
                                 title TEXT NOT NULL,
                                  source TEXT NOT NULL,
                                   timestamp TEXT NOT NULL,
                                   text TEXT NOT NULL);'''

    cursor = sqlite_connection.cursor()
    cursor.execute(sqlite_create_table_query)
    sqlite_connection.commit()

    cursor.close()

except sqlite3.Error as error:
    print("Error to connect to sqlite", error)
finally:
    if (sqlite_connection):
        sqlite_connection.close()