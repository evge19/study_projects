import sqlite3


######################################################
### creation of db
######################################################
# try:
#     sqlite_connection = sqlite3.connect('assignments_db.db')
#     sqlite_create_table_query = '''CREATE TABLE Assignments (
#                                 id INTEGER PRIMARY KEY,
#                                 question TEXT NOT NULL,
#                                  answers TEXT NOT NULL);'''

#     cursor = sqlite_connection.cursor()
#     cursor.execute(sqlite_create_table_query)
#     sqlite_connection.commit()

#     cursor.close()

# except sqlite3.Error as error:
#     print("Error to connect to sqlite", error)
# finally:
#     if (sqlite_connection):
#         sqlite_connection.close()

######################################################
### insert row
######################################################

# try:
#     sqlite_connection = sqlite3.connect('assignments_db.db')
#     cursor = sqlite_connection.cursor()
#     print("Подключен к SQLite")

#     sqlite_insert_query = """INSERT INTO Assignments
#                           (id, question, answers)
#                           VALUES
#                           (5, 'Find the right weights and bias and put the answer at the form (b,w[0],w[1]).\nx=[(1,2),(3,2),(2,1),(3,3)]  y=[-1,1,-1,1]  b0=0, w0=(3,2)', '(-18,2,0)@(0,5,2)@(-18,3,1)@(0,6,4)@(-18,5,2)');"""
#                           #(4, 'Which function is used to define the threshold for classification of two classes?', 'sign');"""
#                           #(3, 'Perceptron has problems with linearly non-separable data.', 'True@False@Depends on the threshold');"""
#                           #(2, 'PLA assumption:', 'y must be -1 or +1 (y=[-1,+1])@initial weights and bias must be zeros@number of classes` examples must be equal');"""
#                           #(1, 'What is FALSE based on Novikoff theorem?', 'Radius is the distance from the center to the farthest point of the positive class.@If the classes are close to each other, then the margin is small, and more mistakes can be done.@A bound of the number of perceptron mistakes can be determined via Novikoff theorem.');"""
                          
                       
#     count = cursor.execute(sqlite_insert_query)
#     sqlite_connection.commit()
#     print("Запись успешно вставлена ​​в таблицу sqlitedb_developers ", cursor.rowcount)
#     cursor.close()

# except sqlite3.Error as error:
#     print("Ошибка при работе с SQLite", error)
# finally:
#     if sqlite_connection:
#         sqlite_connection.close()
#         print("Соединение с SQLite закрыто")

######################################################
### show rows
######################################################

def read_sqlite_table():
    try:
        sqlite_connection = sqlite3.connect('assignments_db.db')
        cursor = sqlite_connection.cursor()
        print("Подключен к SQLite")

        sqlite_select_query = """SELECT * from Assignments"""
        cursor.execute(sqlite_select_query)
        records = cursor.fetchall()
        print("Всего строк:  ", len(records))
        for row in records:
            print(row[0],row[1],row[2])

        cursor.close()

    except sqlite3.Error as error:
        print("Ошибка при работе с SQLite", error)
    finally:
        if sqlite_connection:
            sqlite_connection.close()

read_sqlite_table()

######################################################
### delete rows
######################################################

# def delete_row():
#     try:
#         sqlite_connection = sqlite3.connect('assignments_db.db')
#         cursor = sqlite_connection.cursor()
#         print("Подключен к SQLite")

#         sql_delete_query = """DELETE from Assignments where id = 1"""
#         # sql_delete_query = """DELETE from Assignments where id = 2"""
#         # sql_delete_query = """DELETE from Assignments where id = 3"""
#         # sql_delete_query = """DELETE from Assignments where id = 4"""
#         # sql_delete_query = """DELETE from Assignments where id = 5"""
#         cursor.execute(sql_delete_query)
#         sqlite_connection.commit()
#         print("Запись успешно удалена")
#         cursor.close()

#     except sqlite3.Error as error:
#         print("Ошибка при работе с SQLite", error)
#     finally:
#         if sqlite_connection:
#             sqlite_connection.close()
#             print("Соединение с SQLite закрыто")

# delete_row()