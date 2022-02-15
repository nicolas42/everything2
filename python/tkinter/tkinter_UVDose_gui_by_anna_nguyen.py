### Reference to Anna Nguyen, 2018
#
# pip install serial pytz pyserial
#


if __name__ == "__main__":

    from tkinter import *
    import tkinter as tk
    import time
    import serial
    import threading
    from tkinter import messagebox
    from datetime import datetime
    import pytz
    import serial.tools.list_ports as port_list
    
        

    today = datetime.today()
    d1 = today.strftime("%d/%m/%Y")
    print("d1 =", d1)


    ports = ["COM4", "COM13"]
    override = ["N/A", "1", "2", "3", "4", "5", "6"]

    traits = ["Genetic (physical traits)", "Sensitivity (reaction to sun exposure)",
            "Intentional Exposure (tanning habits)"] ### list

    questions = ["What are the colour of your eyes?",
                "What is the colour of your hair (naturally and before aging)?",
                "What is the colour of your skin (unexposed areas)?",
                "Do you have freckles on unexposed areas?",
                "What happens to your skin if you stay in the sun for an extended " +
                "period?",
                "Do you turn brown after sun exposure?",
                "How brown do you get?",
                "Is your face sensitive to the sun?",
                "How often do you tan?",
                "When did you last expose your skin to the sun or artificial " +
                "tanning sources (tanning beds)?"]

    answers0 = ["Light blue or green, grey", "Blue, green, grey", "Dark blue or "
                +"green, light brown (hazel)", "Dark brown", "Brownish black"]
    answers1 = ["Red", "Blonde", "Chestnut or dark blonde", "Datk brown", "Black"]
    answers2 = ["Pink", "Very pale", "Light brown or olive", "Brown", "Dark brown"]
    answers3 = ["Many", "Several", "Few", "Rare", "None"]

    answers4 = ["Severe burns, blistering, peeling", "Moderate burns, blistering " +
                "peeling", "Burns sometimes followed by peeling", "Rare burns",
                "No burns"]
    answers5 = ["Never", "Rarely", "Sometimes", "Often", "Always"]
    answers6 = ["Hardly or not at all", "Light tan", "Medium tan", "Dark tan",
                "Very dark tan"]
    answers7 = ["Very sensitive", "Sensitive", "Mildly sensitive", "Resistant",
                "Very resistant"]
    answers8 = ["Never", "Rarely", "Sometimes", "Often", "Always"]
    answers9 = ["More than three months ago", "In the last 2-3 months",
                "In the last 1-2 months", "In the last week", "In the last day"]
                
    answers = [answers0, answers1, answers2, answers3, answers4, answers5,
            answers6, answers7, answers8, answers9]

    max_answer_len = 0
    for answer_list in answers:
        for answer in answer_list:
            
            if len(answer) > max_answer_len:
                max_answer_len = len(answer)

    max_question_len = 0
    for question in questions:
        if len(question) > max_question_len:
            max_question_len = len(question)
    max_len = max(max_answer_len, max_question_len)

    max_traits_len = 0
    for trait in traits:
        if len(trait) > max_traits_len:
            max_traits_len = len(trait)


    is_open = 0
    MCU_ack = 0
    time_ack = 0
    current_port = "current"
    thread = 0
    current_question_number = 0
    MED = 0
    score = 0
    prev_answer = 0
    answer_buffer = [0] * 10

    MED_buffer = ['N/A', 150, 220, 290, 370, 440, 440]
    skin_type_buffer = ['N/A', 'I', 'II', 'III', 'IV', 'V', 'VI']

    first_connect = 0


    ser = serial.Serial(
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
    )

    root = tk.Tk()

    override_var = StringVar(root)
    override_var.set("N/A") #Default Value

    space1int = 8
    space2int = 11
    quizspace1 = 1


    root.title("UVDose")
    root.geometry("600x400")
    def check_port():
        """Checks if USB port is connected

        Reads from port every second. If no connection is detected then raise an
        exception.

        Args:
            None

        Returns:
        None

        Raises:
            Disconnection Error - Port not open
        """
        
        global is_open
        global MCU_ack
        global time_ack
        global first_connect
        if(is_open):

            if first_connect == 1:
                    ack = "ack@"
                    ser.write(ack.encode())
                    time.sleep(0.1)
                    connect_port()
                    ser.write(ack.encode())
                    time.sleep(0.1)
                    connect_port()
                    ser.write(ack.encode())

                    s = ser.readline()  #Attempt to read from port   
                    UV_value.config(text = s.decode())
                    first_connect = 0
            try:
            
                if time_ack == 1:
                    timeStr = "time@"
                    ser.write(timeStr.encode())

                    s = ser.readline()
                    time_value.config(text = s.decode())
                
                ack = "ack@"
                a = "a"
                c = "c"
                k = "k"
                end = "@"
                ser.write(ack.encode())
            
                s = ser.readline()  #Attempt to read from port   
                UV_value.config(text = s.decode())
            except Exception:
                print("error\n\r")  #Show error if no connection
                disc_error = messagebox.showerror("Error", "Serial disconnected, " +
                                                "please reconnect")
                is_open = 0
                MCU_ack = 0
                ser.close()
                port_label1.config(text = "Choose an open port")
                refresh()

        root.after(750, check_port) #Check connection every second


    check_port()


    def refresh():
        """Refreshes port list

        Reads serial port list and updates tkinter listbox

        Args:
            None

        Returns:
        None

        Raises:
            None
        """
        global var
        var.set('')
        port_menu['menu'].delete(0, 'end')
        ports = list(port_list.comports())
        for port in ports:
            port_menu['menu'].add_command(label= port, command=tk._setit(var, port))
        

    def connect_port():
        """Connects to port

        Attempts to connect to a chosen, open port

        Args:
            None

        Returns:
        None

        Raises:
            None
        """

        portStr = var.get()

        words = portStr.split(' ')
        print(words[0])
        ser.port = words[0]

        if(ser.isOpen() == False):  #Open connection if port not already open
            
            ser.open()
        global is_open
        global MCU_ack
        is_open = 1
        MCU_ack = 1
        global first_connect
        first_connect = 1 
        port_label1.config(text = "Connected to: " + words[0])
        

            

        
        


    def sync_time():
        global time_ack
        time_ack = 1


    def update_MED_details():
        global MED_label
        global skin_type_label
        global skin_type
        MED_label.config(text = 'MED: ' + str(MED_buffer[skin_type]))
        skin_type_label.config(text = 'Skin Type: '
                                + skin_type_buffer[skin_type])


    def button_next():
        
        global current_question_number
        global prev_answer
        global quiz
        global skin_type
        error_flag = 0

        try:
            answer_index = answers_list.curselection()[0]
            
        except IndexError:
            error_flag = 1

        if (error_flag == 0):
            answer_buffer[current_question_number] = answer_index
                
            
        elif (error_flag == 1):
            error1 = messagebox.showerror("Error", "Please choose an option "+
                                        "from the list")
            
        if current_question_number < 9:
            current_question_number += 1
            if current_question_number < 4:
                trait_label.config(text = traits[0])
            elif (current_question_number >=4) & (current_question_number < 8):
                trait_label.config(text = traits[1])
            
            else:
                trait_label.config(text = traits[2])

            question_label.config(text = questions[current_question_number])
            for i in range(5):
                answers_list.insert(i, answers[current_question_number][i])
        else:
            quiz.destroy()
            send_MED_button.config(state = NORMAL)
            total = 0
            for i in range(10):
                total = total + answer_buffer[i]
            skin_type = 0
            if (total <= 6):
                skin_type = 1
            elif (total >= 7) & (total <= 13):
                skin_type = 2
            elif (total >= 14) & (total <= 20):
                skin_type = 3
            elif (total >= 21) & (total <= 27):
                skin_type = 4
            elif (total >= 28) & (total <= 34):
                skin_type = 5
            else:
                skin_type = 6

            update_MED_details()
            current_question_number = 0
                
                
            
        return 0


    def button_back():
        global current_question_number
        global answer
        
        if current_question_number > 0:
            current_question_number -= 1
            if current_question_number < 4:
                trait_label.config(text = traits[0])
            elif (current_question_number >=4) & (current_question_number < 8):
                trait_label.config(text = traits[1])
            
            else:
                trait_label.config(text = traits[2])

            question_label.config(text = questions[current_question_number])
            for i in range(5):
                answers_list.insert(i, answers[current_question_number][i])        
        return 0

        
    def start_test():

        question_number = 0
        total_question= 9
        global quiz
        
        quiz = tk.Toplevel(root)
        ### ARPANSA Quiz
        quiz.title("ARPANSA Quiz")
        quiz.geometry("900x200")

        ### Spaces
        quiz_space1 = tk.Label(quiz, anchor = 'c')
        quiz_space1.grid(row = 1, column = 0)

        quiz_space2 = tk.Label(quiz, anchor = 'c')
        quiz_space2.grid(row = 5, column = 0)



        ### Title
        frame = tk.Frame(quiz, height = 10, width = 300)
        frame.grid(row=0,column=0, columnspan = 3)
        frame.grid_propagate(0)
        quiz_title_label = tk.Label(frame, text = "ARPANSA Quiz", anchor = "c")
        quiz_title_label.place(x=150, y=5, anchor="c")


        ### Question
        global trait_label
        trait_label = tk.Label(quiz, text = traits[0], anchor = 'c',
                            width = 30)
        trait_label.grid(row = 2, column = 0)

        global question_label
        question_label = tk.Label(quiz, text = questions[0], anchor = 'c')
        question_label.grid(row = 2, column = 2, sticky = W)

        global answers_list
        answers_list = tk.Listbox(quiz, height = 5, width = 85)
        for i in range(5):
            answers_list.insert(i, answers[0][i])

        answers_list.grid(row = 3, column = 2, sticky = W)

        ### Next/Back buttons
        next_button = tk.Button(quiz, text = 'Next', anchor = 'c',
                                command = button_next)
        next_button.grid(row = 6, column = 3)

        back_button = tk.Button(quiz, text = 'Back', anchor = 'c',
                                command = button_back)
        back_button.grid(row = 6, column = 1)    
        

    def override_option(value):
        global skin_type
        global send_MED_button
        if (len(value) != 1):
            print('here')
            send_MED_button.config(state = DISABLED)
            skin_type = 0
            update_MED_details()
        else:
            skin_type = int(value)
            send_MED_button.config(state = NORMAL)
            update_MED_details()
            
        return 0

    def disconnect():
        global is_open
        global MCU_ack
        global time_ack
        dis = "dis@"
        ser.write(dis.encode())
        MCU_ack = 0
        is_open = 0
        time_ack = 0;
        ser.close()
        port_label1.config(text = "Disconnected")

    def send_MED():
        global skin_type
        MED = str(MED_buffer[skin_type])
        MCU_MED = "!" + str(skin_type) + MED + "@"
        print(MCU_MED)
        ser.write(MCU_MED.encode())
        s = ser.readline()
        print(s.decode())

    def rtc():

        timezone = pytz.timezone('Australia/Brisbane')
        rtc_datetime = datetime.now(timezone)
        
        year = rtc_datetime.strftime("%y")
        hex_year = "0x" + year
        hex_year_int = int(hex_year, 16)
        

        month = rtc_datetime.strftime("%m")
        hex_month = "0x" + month
        hex_month_int = int(hex_month, 16)
        #ser.write(hex_month_int.encode())

        date = rtc_datetime.strftime("%d")
        hex_date = "0x" + date
        hex_date_int = int(hex_date, 16)
        #ser.write(hex_date_int.encode())

        hour = rtc_datetime.strftime("%H")
        hex_hour = "0x" + hour
        hex_hour_int = int(hex_hour, 16)
        #ser.write(hex_hour_int.encode())

        minute = rtc_datetime.strftime("%M")
        hex_minute = "0x" + minute
        hex_minute_int = int(hex_minute, 16)
        #ser.write(hex_minute_int.encode())

        second = rtc_datetime.strftime("%S")
        hex_second = "0x" + second
        hex_second_int = int(hex_second, 16)
        #ser.write(hex_second_int.encode())

        rtc = "rtc" + hex_year + hex_month + hex_date + hex_hour + hex_minute + hex_second + "@"
        print(rtc)
        ser.write(rtc.encode())



    ### GUI Title
    main_frame1 = tk.Frame(root, height = 20, width = 400)
    main_frame1.grid(row = 0, column = 0, columnspan = 4)
    main_frame1.grid_propagate(0)

    main_frame2 = tk.Frame(root, height = 20, width = 400)
    main_frame2.grid(row = 1, column = 0, columnspan = 4)
    main_frame2.grid_propagate(0)

    title_label_1 = tk.Label(main_frame1, text = "ENGG3800 Group 02", anchor = "c")
    title_label_1.place(x = 160, y = 5)

    title_label_2 = tk.Label(main_frame2, text = "UVDose", anchor = "c")
    title_label_2.place(x = 190, y = 5)


    start = tk.Button(root, text = 'Start Test', anchor = 'c', command = start_test)
    start.grid(row = 4, column = 0)

    global skin_type_label
    skin_type_label = tk.Label(root, text = 'Skin Type: ' + override[0] , anchor = 'c')
    skin_type_label.grid(row = 4, column = 1)

    global MED_label
    MED_label = tk.Label(root, text = 'MED: ', anchor = 'c')
    MED_label.grid(row = 4, column = 2)


    ### Override
    override_button = tk.Label(root, text = 'Override Skin Type', anchor = 'c')
    override_button.grid(row = 3, column = 3)

    override_menu = tk.OptionMenu(root, override_var, *override,
                                command = override_option)
    override_menu.grid(row = 4, column = 3)

    ###Send
    global send_MED_button
    send_MED_button = tk.Button(root, text = 'Send to Device', anchor = 'c',
                        state = DISABLED, command = send_MED)
    send_MED_button.grid(row = 4, column = 4)



    ### UV Reading
    UV_label = tk.Label(root, text = 'UV Reading', anchor = 'c')
    UV_label.grid(row = space1int + 1, column = 0)

    UV_value = tk.Label(root, text = 'N/A', anchor = 'c')
    UV_value.grid(row = space1int + 2, column = 0)

    ### Time Reading
    time_label = tk.Label(root, text = 'Time', anchor = 'c')
    time_label.grid(row = space1int + 1, column = 1)

    time_value = tk.Label(root, text = 'N/A', anchor = 'c')
    time_value.grid(row = space1int + 2, column = 1)



    ##Sync Time
    time_sync_button = tk.Button(root, text = 'Synchronise Time', anchor = 'c',
                                command = sync_time)
    time_sync_button.grid(row = space1int + 1, column = 3)

    rtc_send_button = tk.Button(root, text = 'Init time', anchor = 'c',
                                command = rtc)
    rtc_send_button.grid(row = space1int + 1, column = 4)


    ##Choose serial port

    port_label1 = tk.Label(root, text = "Currently connected to:", anchor = 'c')
    port_label1.grid(row = space2int + 1, column = 0)

    port_refresh = tk.Button(root, text = "Refresh ports", anchor = 'c',
                            command = refresh)
    port_refresh.grid(row = space2int + 3, column = 1)

    var = tk.StringVar(root)

    port_menu_label = tk.Label(root, text = "Select Port", anchor = 'c')
    port_menu_label.grid(row = space2int + 1, column = 1)

    port_menu = tk.OptionMenu(root, var, *ports)
    port_menu.grid(row = space2int + 2, column = 1)

    port_button_connect = tk.Button(root, text = "Connect", anchor = 'c',
                        command = connect_port)
    port_button_connect.grid(row = space2int + 1, column = 3)

    port_button_disconnect = tk.Button(root, text = "Disonnect", anchor = 'c',
                        command = disconnect)
    port_button_disconnect.grid(row = space2int + 2, column = 3)


    ##Spaces
    space1 = tk.Label(root, text = '', anchor = 'c')
    space1.grid(row = space1int, column = 3)

    space2 = tk.Label(root, text = '', anchor = 'c')
    space2.grid(row = space2int, column = 3)



    root.mainloop()














