from email.policy import default
import PySimpleGUI as sg
import numpy as np
import sqlite3
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import Pipeline
import time

######################################################
# task option (later will be combined with questions)
######################################################

# initialization of necessery parameters
close=False
q_counter=4
user_cor=0
task_attempt=0
task_answer=''
solution_shown = 0
step_show = 0
showstep=0

# training dataset for the classification how the student understands the topic
sg.theme('GrayGrayGray')

X_train = [(30,0,0),(27,0,1),(40,0,0),(10,1,2),(15,1,0),(25,0,2),(50,0,0),(18,0,2),(37,0,1),(15,0,3),(30,0,1),(35,0,1),(15,1,3),(40,1,1)] # the features we want to analyze
y_train = [0,0,0,1,1,0,0,1,0,0,0,1,1,1] # the labels, or answers, we want to test against

classifier = LogisticRegression()
pipe = Pipeline([('classifier', classifier)])
pipe.fit(X_train,y_train)


# classifier. gives the text about topic undrerstanding
def get_classifier(task,solu,step_show):
    test=[[task,solu,step_show]]
    predicted = pipe.predict(test)
    if predicted==0:
        res="Well done!"
    else:
        res="Not very good."
    return res

# shows steps on the screen
def show_step(n):
    steps=read_sqlite_table(4,2)
    k=n+1
    st="step"+str(k)
    window[st].update("{}".format(steps[n]),disabled = True)
    window['ans'+str(k)].update("{}".format(""))

# checks steps and shows correct / wrong on the screen
def check_steps(st1,st2,st3,st4):
    steps=read_sqlite_table(4,2)
    if(st1==steps[0]):
        window['ans1'].update("{}".format("Correct"))
        window["step1"].update("{}".format(st1),disabled = True)
    else:
        window['ans1'].update("{}".format("Wrong"))
    if(st2==steps[1]):
        window['ans2'].update("{}".format("Correct"))
    else:
        window['ans2'].update("{}".format("Wrong"))
    if(st3==steps[2]):
        window['ans3'].update("{}".format("Correct"))
    else:
        window['ans3'].update("{}".format("Wrong"))
    if(st4==steps[3]):
        window['ans4'].update("{}".format("Correct"))
    else:
        window['ans4'].update("{}".format("Wrong"))

# checks the task final answer and shows correct / wrong on the screen layout_task
def check_ans_task(ans):
    steps=read_sqlite_table(q_counter, 2)
    if(ans==steps[-1]):
        window['-cor_answer_task-'].update("{}".format("Correct"))
        window['-finish-'].update(disabled = False)
    else:
        window['-cor_answer_solu-'].update("{}".format("Wrong"))
        
        window[f'-lay_task-'].update(visible=False)
        window[f'-lay_solu-'].update(visible=True)
        window['user_ans_solu'].update("{}".format(ans))

    return task_answer

# checks the task final answer and shows correct / wrong on the screen layout_solution with steps
def check_ans_solu(ans):
    steps=read_sqlite_table(q_counter, 2)
    if(ans==steps[-1]):
        window['-cor_answer_solu-'].update("{}".format("Correct"))
        window['-finishsolu-'].update(disabled = False)
    else:
        window['-cor_answer_solu-'].update("{}".format("Wrong"))

# shows task text from db at the screen
def show_task(q_counter):
    window['task'].update("{}".format(read_sqlite_table(q_counter, 3)))

# changes the text in chatbot based on user input layout_task
def get_answer(user_input):
    window['chatbot_show'].update("{}".format("for later"))

# changes the text in chatbot based on user input layout_solution
def get_answer_task(user_input_task):
    window['chatbot_show_task'].update("{}".format("for later"))

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
            print("Ошибка при работе с SQLite", error)
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

task_text=read_sqlite_table(4, 3) # task text

######################################################
# set layouts and their frames
######################################################

task_frame=[[sg.Multiline(task_text, key='task', font='Helvetica 12', size=(300, 6), disabled = True, background_color="#f0f0f0")], [sg.InputText(size=(20, 1),  key="user_ans_task")],[sg.Button('Check',enable_events=True, key='-check_ans_task-', font='Helvetica 12', button_color="#a7c4f4"),sg.Text('', size=(50, 1), key='-cor_answer_task-', font='Helvetica 12'),
                      sg.Button('Finish',enable_events=True, key='-finish-', font='Helvetica 12', button_color="#a9c3c8", disabled = True)],[sg.Text('', key='clue', font='Helvetica 12')]]

solution_frame=[[sg.Multiline(task_text, key='task', font='Helvetica 12', size=(300, 6), disabled = True, background_color="#f0f0f0")], [sg.InputText(size=(20, 1),  key="user_ans_solu")],[sg.Button('Check',enable_events=True, key='-check_ans_solu-', font='Helvetica 12', button_color="#a7c4f4"),sg.Text('', size=(50, 1), key='-cor_answer_solu-', font='Helvetica 12'),
                      sg.Button('Finish',enable_events=True, key='-finishsolu-', font='Helvetica 12', button_color="#a9c3c8", disabled = True)],
                      [sg.Text('Check the intermediate steps:', key='inter', font='Helvetica 12')],
                      [sg.Text('Step 1', font='Helvetica 12'), sg.InputText(size=(20, 1),  key="step1"), sg.Text('', key='ans1', font='Helvetica 12')],
                      [sg.Text('Step 2', font='Helvetica 12'), sg.InputText(size=(20, 1),  key="step2"), sg.Text('', key='ans2', font='Helvetica 12')],
                      [sg.Text('Step 3', font='Helvetica 12'), sg.InputText(size=(20, 1),  key="step3"), sg.Text('', key='ans3', font='Helvetica 12')],
                      [sg.Text('Step 4', font='Helvetica 12'), sg.InputText(size=(20, 1),  key="step4"), sg.Text('', key='ans4', font='Helvetica 12')],
                      [sg.Text('', size=(10, 5))],
                      [sg.Button('Check steps',enable_events=True, key='-checksteps-', font='Helvetica 12', button_color="#a7c4f4"),
                      sg.Button('Show next step',enable_events=True, key='-Shownextstep-', font='Helvetica 12', button_color="#fbe6a3"),
                      sg.Button('Show solution',enable_events=True, key='-Showsolution-', font='Helvetica 12', button_color="#f2cda2")]]
chatbot_frame=[[sg.Multiline('Hello! You can ask me!', size=(100, 20), key='chatbot_show', font='Helvetica 12', background_color ="#f3f7f0")],
 [sg.InputText(size=(30, 1), key="user_input"), sg.Button('Go',enable_events=True, key='-ask-', button_color="#bcd6ac", size=(6, 1), font='Helvetica 12')]]

chatbot_frame_task=[[sg.Multiline('Hello! You can ask me!', size=(100, 20), key='chatbot_show_task', font='Helvetica 12', background_color ="#f3f7f0")],
 [sg.InputText(size=(30, 1), key="user_input_task"), sg.Button('Go',enable_events=True, key='-asktask-', button_color="#bcd6ac", size=(6, 1), font='Helvetica 12')]]

solution_layout = [[sg.Frame('Task',  solution_frame, size=(650,500)),sg.Frame('Chatbot', chatbot_frame, size=(350,500), background_color ="#dedede")]]
task_layout = [[sg.Frame('Task',  task_frame, size=(650,500)),sg.Frame('Chatbot', chatbot_frame_task, size=(350,500), background_color ="#dedede")]]

initial_layout=[[sg.Text('', size=(112, 1)),sg.Button('Start',enable_events=True, key='start', font='Helvetica 12')],
                [sg.Text('',key='stat_title')],
                [sg.Text('', size=(11, 1))],
                [sg.Text('', key='statistics')],
                [sg.Text('', key='trytosee',font='bold',text_color="#12163b")]]

# all layouts
layout = [[sg.Column(initial_layout, key='-lay_init-'), sg.Column(solution_layout, visible=False, key='-lay_solu-'), sg.Column(task_layout, visible=False, key='-lay_task-')]]

# creates the window
window = sg.Window('Perceptron', layout, size=(1000,500))

######################################################
# events
######################################################

while True:
    event, values = window.read()
    if event in (sg.WIN_CLOSED, 'Exit'):
        break
    if event == '-finishsolu-':
        task_time = round(time.time()-start_time, 2)
        button_text = ""

        window['stat_title'].update('Statistics for the session',font='Helvetica 13')

        result=get_classifier(task_time,solution_shown,step_show)
        stati = 'Spent time on task: ' + str(task_time) + 'sec\n\n'

        window['statistics'].update(stati)
        window['trytosee'].update(result)

        close=True
        window['start'].update('Close')
        window[f'-lay_solu-'].update(visible=False)
        window[f'-lay_init-'].update(visible=True)
    if event == '-finish-':
        task_time = round(time.time()-start_time, 2)
        window['start'].update('Close')
        window['stat_title'].update('Statistics for the session',font='Helvetica 13')



        result=get_classifier(task_time,solution_shown,step_show)
        stati = 'Spent time on task: ' + str(task_time) + 'sec\n\n'

       
        window['statistics'].update(stati)
        window['trytosee'].update(result)

        close=True
        window[f'-lay_task-'].update(visible=False)
        window[f'-lay_init-'].update(visible=True)
    if event == 'start':
        if(close==True):
            window.close()
        else:
            window[f'-lay_init-'].update(visible=False)
            window[f'-lay_task-'].update(visible=True)
            start_time = time.time()
    if event == '-ask-':
        get_answer(window['user_input'].get())
    if event == '-asktask-':
        get_answer_task(window['user_input_task'].get())
    if event == '-check_ans_task-':
        check_ans_task(window['user_ans_task'].get())
        task_attempt+=1
    if event == '-check_ans_solu-':
        check_ans_solu(window['user_ans_solu'].get())
        task_attempt+=1
    if event =='-checksteps-':
        check_steps(window['step1'].get(),window['step2'].get(), window['step3'].get(), window['step4'].get())
    if event=='-Shownextstep-':
        step_show += 1
        show_step(showstep)
        if showstep==3:
            window["-Shownextstep-"].update(disabled = True)
            window["-checksteps-"].update(disabled = True)
        showstep+=1
    if event=="-Showsolution-":
        solution_shown = 1
        for i in range(4):
            show_step(i)
        steps=read_sqlite_table(q_counter, 2)
        window["user_ans_solu"].update("{}".format(steps[-1]),disabled = True)
        window['-finishsolu-'].update(disabled = False)
        window["-Shownextstep-"].update(disabled = True)
        window["-Showsolution-"].update(disabled = True)
        window["-checksteps-"].update(disabled = True)
        window['-cor_answer_solu-'].update("{}".format(""))
        

window.close()

