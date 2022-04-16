from tkinter import *
from tkinter import filedialog
from PIL import Image, ImageTk
import numpy as np
import matplotlib.pyplot as plt
import tkinter.ttk as ttk

x = []
y = []
data = []
file = ''

# вывод изображения
def show(img):
    plt.imshow(img, cmap=plt.get_cmap('gray'))
    plt.show()

# преобразование в оттенки серого
def to_black(img):
    return img.convert('L')

# Загрузка капчи из файловой системы
def getFile():
    global file
    global lbl0
    file = filedialog.askopenfilename()

    img = Image.open(file)
    plt.imshow(img, cmap=plt.get_cmap('gray'))
    plt.savefig("1.png")
    plt.clf()

    img = Image.open('1.png')
    img = ImageTk.PhotoImage(img)
    lbl = Label(image=img)
    lbl.image = img
    lbl.place(x=20, y=230)

    lbl0.destroy()

# Расчёт значений и построение графика
def calculate():
    global lbl0
    x.clear()
    y.clear()
    data.clear()

    # получение ширины
    n = int(txt1.get())
    n = int(n/2) # n - середина фильтра

    # получение шага
    h = int(txt2.get())

    global file

    # получение изображения
    img = Image.open(file)

    # преобразование изображения в массив чисел
    img = np.array(to_black(img))
    l = sum(img[:, 0])
    r = sum(img[:, len(img[0])-1])

    # Расчёт для левой границы
    for i in range(0, n, h):
        a = 0
        b = 0
        for j in range(n):
            if (j < (n-i)):
                a = a + l
            else:
                a = a + sum(img[:,i+j])
        for j in range(n):
            b = b + sum(img[:,i+j])
        x.append(i)
        y.append(b-a)
        data.append([i, b-a])

   # Расчёт для остальной части капчи
    for i in range(0, len(img[0]), h):
        if (i+2*n < len(img[0])):
            a = 0
            b = 0
            for j in range(n):
                a = a + sum(img[:,i+j])
            for j in range(n):
                b = b + sum(img[:,i+j+n])
            x.append(i+n)
            y.append(b-a)
            data.append([i+n, b-a])

    # Добавление к графику координатной сетки
    # и сохранение картинки
    fig, ax = plt.subplots()
    ax.plot(x, y, color ='g', linewidth=2)
    ax.grid(which='major', color = 'k')
    ax.minorticks_on()
    ax.grid(which='minor', color ='gray', linestyle = ':')
    plt.savefig("graph.png")
    plt.clf()

    # построение таблицы
    table = ttk.Treeview(window)
    table['columns'] = ('X', 'Y')

    table.column('#0', width=0, stretch=NO)
    table.column('X', anchor=CENTER, width=80)
    table.column('Y', anchor=CENTER, width=80)

    table.heading('#0', text='', anchor=CENTER)
    table.heading('X', text='X', anchor=CENTER)
    table.heading('Y', text='Y', anchor=CENTER)

    for i in data:
        table.insert(parent='', index=0, values=i)

    table.place(x=1000,y=5)

    # вывод графика на экран
    graph = Image.open('graph.png')
    graph = ImageTk.PhotoImage(graph)
    lbl0 = Label(image=graph)
    lbl0.image = graph
    lbl0.place(x=680, y=230)



# Окно приложения
window = Tk()
window.title("МиСОС ЛР2")
window.minsize(1330, 720)
window.config(bg="light green")

# Основной заголовок
label_main = Label(window, text='Распознование букв в капче',
                      font=('Comic Sans MS', 15, 'bold'),
                      height=3,
                      relief=RAISED,
                      bd=8,
                      bg="YELLOW")

# Заголовок для графика
lbl0 = Label()

# Поля ввода
txt1 = Entry(window, font=('Comic Sans MS', 8, ), width=18)
txt2 = Entry(window, font=('Comic Sans MS', 8, ), width=18)

# Заголовки для полей ввода
lbl1 = Label(window, text="Введите ширину фильтра:  ", font=('Comic Sans MS', 20, 'bold'),bg="light green")
lbl2 = Label(window, text="Введите шаг сдвига:  ", font=('Comic Sans MS', 20, 'bold'),bg="light green")


# Кнопка для рассчёта
btn = Button(window, text="Вычислить",
             font=('Comic Sans MS', 15, 'bold'),
             command=calculate,
             cursor="mouse",
             bg="light blue")

# Кнопка для добавления изображения
btn1 = Button(window, text="Добавить изображение",
              font=('Comic Sans MS', 15, 'bold'),
              bg="light blue",
              cursor="mouse",
              command=getFile)

# Расположение элементов
label_main.place(x=105, y=10)
lbl1.place(x=30, y=120)
lbl2.place(x=30, y=170)
txt1.place(x=415, y=135)
txt2.place(x=415, y=185)
btn1.place(x=600, y=30)
btn.place(x=650, y=110)

window.mainloop()