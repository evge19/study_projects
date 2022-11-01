from email.policy import default
import PySimpleGUI as sg

import sqlite3
import random
import time
from spacy.lang.en import English
from spacy.lang.en.stop_words import STOP_WORDS
import spacy
import en_core_web_sm

from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import Pipeline

######################################################
# we assume the material document and database with questions and answers are already exist
######################################################


######################################################
# settings
sg.theme('GrayGrayGray')

# Load English tokenizer, tagger, parser, NER and word vectors
nlp = English()
nlp2 = en_core_web_sm.load()
spacy_stopwords = spacy.lang.en.stop_words.STOP_WORDS

######################################################
# from the text of material row by row create a list of rows

with open("material.txt", "r") as file:
    material = file.read()

all_rows=material.split('.')
file_rows=[]
for row in all_rows:
    row=row.replace('\n', '')
    row+="."
    file_rows.append(row)
file_rows.pop()

# possible keywords
keywords=["weight", "bias", "novikoff", "perceptron", "radius", "margin", "threshold", "bound","class", "assumption", "pla","separable","linearly"]

# initialization of necessery parameters
question_time=[] # list of separate times for each question
q_counter=0      # number of question counter
user_cor=0       # correct answer for multiple choice questions
ques_attempt=0   # number of user`s attempts to check the answer
close=False      # openning and closing button mode

# training dataset for the classification how the student understands the topic
X_train = [(0,15),(4,11),(2,14),(7,28),(9,30),(3,10),(3,40),(12,16),(3,18),(0,13),(2,17),(5,28),(8,20),(6,21)] # features
y_train = [0,1,0,1,1,1,1,1,0,0,0,1,1,1] # labels
classifier = LogisticRegression()
pipe = Pipeline([('classifier', classifier)])
pipe.fit(X_train,y_train)

# classifier. gives the text about topic undrerstanding
def get_classifier(ques_attempt,ques_sum):
    test=[[ques_attempt,ques_sum]]
    predicted = pipe.predict(test)
    if predicted==0:
        res="Well done! You can continue to the next topic!"
    else:
        res="Not very good. Learn the material and try again or explore similar topics."
    return res
######################################################
### button functions
######################################################

# checks the answer of user and shows the result on the screen
def check_ans_task(ans):
    right_ans=read_sqlite_table(q_counter, 2)
    final_t=[]
    if(ans==right_ans[-1]):
        window['-cor_answer_t-'].update("{}".format("Correct"))
        window['clue_task'].update("{}".format(""))
        window['-finish-'].update(disabled = False)
    else:
        window['-cor_answer_t-'].update("{}".format("Wrong"))
        q_q=read_sqlite_table(q_counter, 3)
        a2=twice_nlp(q_q)
        for el in a2:
            final_t.append(el)
            pay="Pay attention to:"
            for el in a2:
                pay+="\n"
                pay+=el
        window['clue_task'].update("{}".format(pay))

# shows the task after questions
def show_task(q_counter):
    read_sqlite_table(q_counter, 4)
    window['task'].update("{}".format(read_sqlite_table(q_counter, 3)))

# shows the respond of chatbot
def get_answer(user_input):
    inel=False
    lem = nlp2(str(user_input))
    for word in lem:
        us_in=word.lemma_
    bot_resp=""
    for el in file_rows:
        if(us_in in el.lower()):
            bot_resp=bot_resp+el
            bot_resp=bot_resp+"\n"
            inel=True
    if inel==False:
        bot_resp="Rephrase your question"
    window['chatbot_show'].update("{}".format(bot_resp))

# changes the text in chatbot based on user input
def get_answer_task(user_input_task):
    window['chatbot_show_task'].update("{}".format("to understand " +user_input_task +" try"))

# gets information from the database based on the user request
def read_sqlite_table(row_num, qa):
    if(qa==1):
        try:
            sqlite_connection = sqlite3.connect('assignments_db.db')
            cursor = sqlite_connection.cursor()
            print("Connected to SQLite")

            sqlite_select_query = """SELECT * from Assignments"""
            cursor.execute(sqlite_select_query)
            records = cursor.fetchall()
            print("Number of rows:  ", len(records))
            all_ans=records[row_num][2].split('@')
            correct_ans=all_ans[0]
            cursor.close()

        except sqlite3.Error as error:
            print("Error with SQLite", error)
        finally:
            if sqlite_connection:
                sqlite_connection.close()
        return correct_ans
    if(qa==2):
        try:
            sqlite_connection = sqlite3.connect('assignments_db.db')
            cursor = sqlite_connection.cursor()
            print("Connected to SQLite")

            sqlite_select_query = """SELECT * from Assignments"""
            cursor.execute(sqlite_select_query)
            records = cursor.fetchall()
            print("Number of rows:  ", len(records))
            all_ans=records[row_num][2].split('@')
            cursor.close()

        except sqlite3.Error as error:
            print("Error with SQLite", error)
        finally:
            if sqlite_connection:
                sqlite_connection.close()
        return all_ans
    if(qa==3):
        try:
            sqlite_connection = sqlite3.connect('assignments_db.db')
            cursor = sqlite_connection.cursor()
            print("Connected to SQLite")

            sqlite_select_query = """SELECT * from Assignments"""
            cursor.execute(sqlite_select_query)
            records = cursor.fetchall()
            print("Number of rows:  ", len(records))
            ques_show=records[row_num][1]
            cursor.close()

        except sqlite3.Error as error:
            print("Error with SQLite", error)
        finally:
            if sqlite_connection:
                sqlite_connection.close()
        return ques_show
    if(qa==4):
        try:
            sqlite_connection = sqlite3.connect('assignments_db.db')
            cursor = sqlite_connection.cursor()
            print("Connected to SQLite")

            sqlite_select_query = """SELECT * from Assignments"""
            cursor.execute(sqlite_select_query)
            records = cursor.fetchall()
            print("Number of rows:  ", len(records))
            ques_show=records[row_num][1]
            cursor.close()

        except sqlite3.Error as error:
            print("Error with SQLite", error)
        finally:
            if sqlite_connection:
                sqlite_connection.close()
        return ques_show

# gets the list of tokens
def twice_nlp(text):
    my_doc = nlp(text)

    # Create list of word tokens
    token_list = []
    for token in my_doc:
        token_list.append(token.text)
    filtered_sent=[]
    for word in token_list:
        if word not in spacy_stopwords:
            if word!="FALSE" and word!="TRUE" and word!="What":
                filtered_sent.append(word.lower())
    final=[]
    for el in filtered_sent:
        lem = nlp2(el)
        for word in lem:
            el=word.lemma_
        if el in keywords:
            final.append(el)
        if el=="bind":
            final.append("bound")
    return final

# defines the words, in which user needs to pay attention
def ques_check_npl(q_counter,a):
    final_t=[]
    q_a=read_sqlite_table(q_counter, 2)
    q_q=read_sqlite_table(q_counter, 3)
    a1=twice_nlp(q_a[a])
    a2=twice_nlp(q_q)
    for el in a1:
        final_t.append(el)
    for el in a2:
        final_t.append(el)
    final_ts = set(final_t)
    return final_ts

# checks the answer and gives necessery info at the screen
def check_answer(q_counter):
    window['clue'].update("{}".format(""))
    right_answer=read_sqlite_table(q_counter, 1)
    if(values["a1"]==True):
        if(user_cor==0):
            window['-cor_answer-'].update("{}".format("Correct"))
            window['-next-'].update(disabled = False)
            window["-check_ans-"].update(disabled = True)
        else:
            window['-cor_answer-'].update("{}".format("Wrong"))
            pay_words=ques_check_npl(q_counter,0)
            pay="Pay attention to:"
            for el in pay_words:
                pay+="\n"
                pay+=el
            window['clue'].update("{}".format(pay))
    elif(values["a2"]==True):
        if(user_cor==1):
            window['-cor_answer-'].update("{}".format("Correct"))
            window['-next-'].update(disabled = False)
            window["-check_ans-"].update(disabled = True)
        else:
            window['-cor_answer-'].update("{}".format("Wrong"))
            pay_words=ques_check_npl(q_counter,1)
            pay="Pay attention to:"
            for el in pay_words:
                pay+="\n"
                pay+=el
            window['clue'].update("{}".format(pay))
    elif((values["a3"]==True)):
        if(user_cor==2):
            window['-cor_answer-'].update("{}".format("Correct"))
            window['-next-'].update(disabled = False)
            window["-check_ans-"].update(disabled = True)
        else:
            window['-cor_answer-'].update("{}".format("Wrong"))
            pay_words=ques_check_npl(q_counter,2)
            pay="Pay attention to:"
            for el in pay_words:
                pay+="\n"
                pay+=el
            window['clue'].update("{}".format(pay))
    else:
        window['-cor_answer-'].update("{}".format("Answer the question"))
    
    
# updates question on the screen
def update_qa(q_counter):
    
    ques_num=q_counter+1
    answers=read_sqlite_table(ques_num, 2)
    window['question'].update("{}".format(read_sqlite_table(ques_num, 3)))
    window['-cor_answer-'].update("{}".format(""))
    window['clue'].update("{}".format(""))
    window['-next-'].update(disabled = True)
    window["-check_ans-"].update(disabled = False)
    f=random.randint(0,2)
    if(f==0):
        s=1
        t=2
        user_cor=0
    elif(f==1):
        s=0
        t=2
        user_cor=1
    else:
        s=1
        t=0
        user_cor=2
    window['a1'].update(text=answers[f], value=False)
    window['a2'].update(text=answers[s], value=False)
    window['a3'].update(text=answers[t], value=False)
    return user_cor

answers=read_sqlite_table(q_counter, 2)
first_ques=read_sqlite_table(q_counter, 3)

######################################################
# set layouts and their frames
######################################################

question_frame=[[sg.Text(first_ques, key='question', font='Helvetica 12')],
                    [sg.Rad(answers[0], 'loss', key="a1")],
                    [sg.Rad(answers[1], 'loss', key="a2")],
                      [sg.Rad(answers[2], 'loss', key="a3")],
                      [sg.Button('Check',enable_events=True, key='-check_ans-', font='Helvetica 12', button_color="#a7c4f4"),sg.Text('', size=(50, 1), key='-cor_answer-', font='Helvetica 12'),
                      sg.Button('Next',enable_events=True, key='-next-', font='Helvetica 12', button_color="#a9c3c8", disabled = True)],[sg.Text('', key='clue', font='Helvetica 12')]]

open_question_frame=[[sg.Text('Open question', key='task', font='Helvetica 12')], [sg.InputText(size=(30, 1),  key="user_ans_task")],[sg.Button('Check',enable_events=True, key='-check_ans_task-', font='Helvetica 12', button_color="#a7c4f4"),sg.Text('', size=(50, 1), key='-cor_answer_t-', font='Helvetica 12'),
                      sg.Button('Next',enable_events=True, key='-finish-', font='Helvetica 12', button_color="#a9c3c8", disabled = True)],
                      [sg.Button('Show solution',enable_events=True, key='-Showsolution-', font='Helvetica 12', button_color="#f2cda2")],[sg.Text('', key='clue_task', font='Helvetica 12')]]

chatbot_frame=[[sg.Multiline('Hello! You can ask me!', size=(100, 20), key='chatbot_show', font='Helvetica 12', background_color ="#f3f7f0")],
 [sg.InputText(size=(30, 1), key="user_input"), sg.Button('Go',enable_events=True, key='-ask-', button_color="#bcd6ac", size=(6, 1), font='Helvetica 12')]]
chatbot_frame_task=[[sg.Multiline('Hello! You can ask me!', size=(100, 20), key='chatbot_show_task', font='Helvetica 12', background_color ="#f3f7f0")],
 [sg.InputText(size=(30, 1), key="user_input_task"), sg.Button('Go',enable_events=True, key='-asktask-', button_color="#bcd6ac", size=(6, 1), font='Helvetica 12')]]

question_layout = [[sg.Frame('Question',  question_frame, size=(650,500)),sg.Frame('Chatbot', chatbot_frame, size=(350,500), background_color ="#dedede")]]

task_layout = [[sg.Frame('Open question',  open_question_frame, size=(650,500)),sg.Frame('Chatbot', chatbot_frame_task, size=(350,500), background_color ="#dedede")]]

initial_layout=[[sg.Text('', size=(112, 1)),sg.Button('Start',enable_events=True, key='start', font='Helvetica 12')],
                [sg.Text('',key='stat_title')],
                [sg.Text('', size=(11, 1))],
                [sg.Text('', key='statistics')],
                [sg.Text('', key='trytosee',font='bold',text_color="#12163b")]]

# all layouts
layout = [[sg.Column(initial_layout, key='-lay_init-'), sg.Column(question_layout, visible=False, key='-lay_ques-'), sg.Column(task_layout, visible=False, key='-lay_open_quest-')]]

# creates the window
window = sg.Window('Perceptron', layout, size=(1000,500))

######################################################
# events
######################################################

while True:
    event, values = window.read()
    if event in (sg.WIN_CLOSED, 'Exit'):
        break
    if event == '-check_ans-':
        check_answer(q_counter)
        ques_attempt+=1
    if event == '-next-':
        question_time.append(round(time.time()-start_time, 2))
        start_time = time.time()
        if q_counter==2:
            q_counter+=1
            window[f'-lay_ques-'].update(visible=False)
            window[f'-lay_open_quest-'].update(visible=True)
            show_task(q_counter)
        else:
            user_cor=update_qa(q_counter)
            q_counter+=1
    if event == 'start':
        if(close==True):
            window.close()
        else:
            start_time = time.time()

            window[f'-lay_init-'].update(visible=False)
            window[f'-lay_ques-'].update(visible=True)
    if event == '-ask-':
        get_answer(window['user_input'].get())
    if event == '-asktask-':
        get_answer_task(window['user_input_task'].get())
    if event == '-check_ans_task-':
        ques_attempt+=1
        check_ans_task(window['user_ans_task'].get())
    if event=='-finish-':
        question_time.append(round(time.time()-start_time, 2))
        print(question_time, round(sum(question_time), 2), ques_attempt)

        window['start'].update('Close')
        window['stat_title'].update('Statistics for the session',font='Helvetica 13')

        whole_time = round(sum(question_time), 2)
        result=get_classifier(ques_attempt,whole_time)

        stati='Number of question responses` attempts: '+str(ques_attempt)+'\n'+'Average time spent on question: '+str(round(whole_time/4, 2))+'sec\n'+'Time spent on all questions: '+str(whole_time)+'sec\n\n'
        window['statistics'].update(stati)
        window['trytosee'].update(result)

        close=True
        window[f'-lay_open_quest-'].update(visible=False)
        window[f'-lay_init-'].update(visible=True)
        
    if event=='-Showsolution-':
        right_ans=read_sqlite_table(q_counter, 2)
        window["-finish-"].update(disabled = False)
        window['user_ans_task'].update("{}".format(right_ans[-1]),disabled = True)
        window["-check_ans_task-"].update(disabled = True)