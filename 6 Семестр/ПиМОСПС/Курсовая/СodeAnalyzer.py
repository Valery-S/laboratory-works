from tkinter import *
from tkinter import filedialog
import tkinter.ttk as ttk
from textwrap import wrap

data = []
file_name=''
t = []
t1 = []
#Чтение содержимого файла в бинарном виде
def read_file():
    global data
    global file_name
    file_name=filedialog.askopenfilename()
    f=open(file_name,'rb')
    data=f.read()
    f.close()
    
    lbl1['text']="Выбран файл  "+file_name
    window.update()
    width = lbl1.winfo_width()

    if width > 700:
        char_width = width / len("Выбран файл  "+file_name)
        wrapped_text = '\n'.join(wrap(("Выбран файл  "+file_name), int(700 / char_width)))
        lbl1['text'] = wrapped_text

#-----------------------------------------------------

#Поиск вызовов прерываний и операций ввода/вывода
def analize ():
    global data
    global t
    global t1
    #log-файл
    file=open ('analize.log','w')
    s="Выбран файл  "+file_name+'\n'
    file.write(s)

    #Таблица прерываний 
    table_interrapt = ttk.Treeview(window)
    table_interrapt['columns'] = ('Адрес', 'Номер прерывания', 'Функция')
    table_interrapt.column('#0', width=0, stretch=NO)
    table_interrapt.column('Адрес', anchor=CENTER, width=120)
    table_interrapt.column('Номер прерывания', anchor=CENTER, width=120)
    table_interrapt.column('Функция', anchor=CENTER, width=120)
    table_interrapt.heading('#0', text='', anchor=CENTER)
    table_interrapt.heading('Адрес', text='Адрес', anchor=CENTER)
    table_interrapt.heading('Номер прерывания', text='Номер прерывания', anchor=CENTER)
    table_interrapt.heading('Функция', text='Функция', anchor=CENTER)

    #Таблица прерываний 
    table_io = ttk.Treeview(window)
    table_io['columns'] = ('Адрес','Команда', 'Адрес порта')
    table_io.column('#0', width=0, stretch=NO)
    table_io.column('Адрес', anchor=CENTER, width=120)
    table_io.column('Команда', anchor=CENTER, width=120)
    table_io.column('Адрес порта', anchor=CENTER, width=120)
    table_io.heading('#0', text='', anchor=CENTER)
    table_io.heading('Адрес', text='Адрес', anchor=CENTER)
    table_io.heading('Команда', text='Команда', anchor=CENTER)
    table_io.heading('Адрес порта', text='Адрес порта', anchor=CENTER)
    
    #Адрес операции
    address=0
    
    #Для всех элементов в массиве
    for i in range(0,len(data)):
        #Проверка на прерывание
        #Если содержимое байта равно 205d(CDh)
        if data[i] == 205:
            #Если содержимое байта, идущего на 2 раньше, равно 180d(B4h)
            if data[i-2]==180:
                string='Адрес: '+hex(address)+' Прерывание № '+hex(data[i+1])+' функция - '+ hex(data[i-1])+'\n'
                t.append([hex(address), hex(data[i+1]), hex(data[i-1])])
                file.write(string)
      
        #Проверка на команды ввода
        #Если содержимое байта равно 228d(E4h)или 229d(E5h),
        #то найдена команда in с явным указание номера порта
        if data [i]== 228 or data [i]== 229:
            string='Адрес: '+hex(address)+' Команда in, номер порта - '+ hex(data[i+1])+'\n'
            t1.append([hex(address),'in', hex(data[i+1])])
            file.write(string)
        #Если содержимое байта равно 236d(ECh)или 237d(EDh),
        #то найдена команда in, номер порта находится в регистре dx
        if data [i]== 236 or data [i]== 237:
            string='Адрес: '+hex(address)+' Команда in, номер порта указан в регистре dx\n'
            t1.append([hex(address),'in', 'в регистре dx'])
            file.write(string)
        #Если содержимое байта равно 108d(6Сh)
        #то найдена команда insb 
        if data [i]== 108: 
            string='Адрес: '+hex(address)+' Команда insb\n'
            t1.append([hex(address),'insb', 'в регистре dx'])
            file.write(string)
        #Если содержимое байта равно 109d(6Dh)
        #то найдена команда insw 
        if data [i]== 109 :
            string='Адрес: '+hex(address)+' Команда insw\n'
            t1.append([hex(address),'inws', 'в регистре dx'])
            file.write(string)

        #Проверка на команды вывода
        #Если содержимое байта равно 230d(E6h)или 232d(E7h),
        #то найдена команда in с явным указание номера порта
        if data [i]== 230 or data [i]== 231:
            string='Адрес: '+hex(address)+' Команда out, номер порта - '+ hex(data[i+1])+'\n'
            t1.append([hex(address),'out', hex(data[i+1])])
            file.write(string)
        #Если содержимое байта равно 238d(EEh)или 239d(EFh),
        #то найдена команда in, номер порта находится в регистре dx
        if data [i]== 238 or data [i]== 239:
            string='Адрес: '+hex(address)+' Команда out, номер порта указан в регистре dx\n'
            t1.append([hex(address),'out', 'в регистре dx'])
            file.write(string)
        #Если содержимое байта равно 110d(6Eh)
        #то найдена команда outsb 
        if data [i]== 110: 
            string='Адрес: '+hex(address)+' Команда outsb\n'
            t1.append([hex(address),'outsb', 'в регистре dx'])
            file.write(string)
        #Если содержимое байта равно 111d(6Fh)
        #то найдена команда outsw 
        if data [i]== 111: 
            string='Адрес: '+hex(address)+' Команда outsw\n'
            t1.append([hex(address),'outsw', 'в регистре dx'])
            file.write(string)
        
                    
        #Увеличение адреса  
        address=address+1
        
    #Вывод таблицы нойденных прерываний    
    for i in t:
          table_interrapt.insert(parent='', index=0, values=i)                     
    table_interrapt.place(x=20,y=250)
    t.clear()
                     
    #Вывод таблицы ввода/вывода   
    for i in t1:
          table_io.insert(parent='', index=0, values=i)                     
    table_io.place(x=520,y=250)
    t1.clear()
#---------------------------------------------------------------------------------------

#Главная функция 
#Окно приложения
window = Tk()
window.title("ПиМОСПС КР")
window.geometry('900x700')
window.resizable(width=0, height=0)
window.config(bg="light green")
    
# Основной заголовок
label_main = Label(window, text='Анализатор кода exe-файла',
                      font=('Comic Sans MS', 15, 'bold'),
                      height=3,
                      relief=RAISED,
                      bd=8,
                      bg="YELLOW")
# Заголовок выбранного файла
lbl1 = Label(window, text="Выбран файл  ",
             font=('Comic Sans MS', 20, 'bold'),
             bg="light green")

# Кнопка для выбора файла
btn = Button(window, text="Выбрать файл",
             font=('Comic Sans MS', 15, 'bold'),
             command=read_file,
             cursor="mouse",
             width=20,
             bg="light blue")
# Кнопка для начала анализа
btn1 = Button(window, text="Проанализировать",
              font=('Comic Sans MS', 15, 'bold'),
              bg="light blue",
              cursor="mouse",
              width=20,
              command=analize)

# Расположение элементов
label_main.place(x=310, y=10)
lbl1.place(y=500, x=20)
btn.place(x=80, y=170)
btn1.place(x=600, y=170)


# Отображение окна
window.mainloop()
