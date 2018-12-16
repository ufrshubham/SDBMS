from tkinter import *


def test():
    pass


def show_about():
    pass


class SdbmsUI(Tk):
    """ This is the core UI class for SDBMS """

    def __init__(self):
        super().__init__()
        self.title("Student Data Management System")
        self.geometry("1000x500")
        self.resizable(0, 0)

        # Menu bar
        self.menu_bar = Menu(master=self)

        # File
        self.file_menu = Menu(master=self.menu_bar, tearoff=0)
        self.file_menu.add_command(label='Add Class', command=test)
        self.file_menu.add_command(label='Delete Class', command=test)
        self.file_menu.add_command(label='Exit', command=self.destroy)
        self.menu_bar.add_cascade(label='File', menu=self.file_menu)

        # Help
        self.help_menu = Menu(master=self.menu_bar, tearoff=0)
        self.help_menu.add_command(label='About', command=show_about)
        self.menu_bar.add_cascade(label='Help', menu=self.help_menu)

        # Set menu_bar as menu
        self.config(menu=self.menu_bar)

        # viewer_frame holds class_list_frame, student_list_frame and details_frame
        self.viewer_frame = Frame(master=self)
        self.class_list_frame = LabelFrame(master=self.viewer_frame, text='Class List', borderwidth=1, relief=GROOVE)
        self.student_list_frame = LabelFrame(master=self.viewer_frame, text='Student List', borderwidth=1, relief=GROOVE)
        self.details_frame = LabelFrame(master=self.viewer_frame, text='Details', borderwidth=1, relief=GROOVE)

        # Pack viewer_frame and child frames
        self.viewer_frame.pack(side=TOP, fill=BOTH, expand=True)
        self.class_list_frame.pack(side=LEFT, fill=BOTH, expand=True)
        self.student_list_frame.pack(side=LEFT, fill=BOTH, expand=True)
        self.details_frame.pack(side=LEFT, fill=BOTH, expand=True)

        # List boxes for the three viewers
        self.class_listbox = Listbox(master=self.class_list_frame)
        self.student_listbox = Listbox(master=self.student_list_frame)
        self.details_listbox = Listbox(master=self.details_frame)

        # Pack child widgets of all the viewer frames
        self.class_listbox.pack(fill=BOTH, expand=True)
        self.student_listbox.pack(fill=BOTH, expand=True)
        self.details_listbox.pack(fill=BOTH, expand=True)

        # Status bar
        self.status_frame = Frame(master=self, borderwidth=1, relief=SUNKEN)
        self.status_frame.pack(side=BOTTOM, fill=X)
        self.status_line = Label(master=self.status_frame, text='Status Line')
        self.status_line.pack(fill=X, expand=True)
