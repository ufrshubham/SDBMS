from tkinter import *


class SdbmsUI(Tk):
    """ This is the core UI class for SDBMS """

    def __init__(self):
        super().__init__()
        self.title("Student Data Management System")
        self.geometry("1000x500")
        self.resizable(0, 0)

        self.class_list_frame = LabelFrame(master=self, text='Class List', borderwidth=1, relief=GROOVE)
        self.student_list_frame = LabelFrame(master=self, text='Student List', borderwidth=1, relief=GROOVE)
        self.details_frame = LabelFrame(master=self, text='Details', borderwidth=1, relief=GROOVE)

        self.class_list_frame.pack(side=LEFT, fill=BOTH, expand=True)
        self.student_list_frame.pack(side=LEFT, fill=BOTH, expand=True)
        self.details_frame.pack(side=LEFT, fill=BOTH, expand=True)

        self.class_listbox = Listbox(master=self.class_list_frame)
        self.student_listbox = Listbox(master=self.student_list_frame)
        self.details_listbox = Listbox(master=self.details_frame)

        self.class_listbox.pack(fill=BOTH, expand=True)
        self.student_listbox.pack(fill=BOTH, expand=True)
        self.details_listbox.pack(fill=BOTH, expand=True)
