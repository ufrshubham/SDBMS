from tkinter import *
from tkinter import messagebox

from sdbms_class import SdbmsClass


class AddClassUI(Tk):
    """ This class creates the GUI for 'Add Class' menu option """

    def __init__(self, parent):
        super().__init__()
        self.__parent = parent
        parent.withdraw()

        self.title('Add new class')
        self.geometry('200x75')
        self.resizable(0, 0)

        frame = LabelFrame(master=self, text='Enter class room number')
        frame.pack()

        self.class_room_number_entry = Entry(master=frame)
        self.class_room_number_entry.pack()

        create_button = Button(master=self, text='Add', command=self.on_add_clicked)
        create_button.pack()

        self.protocol("WM_DELETE_WINDOW", self.on_add_class_closing)
        self.mainloop()

    def on_add_clicked(self):
        class_room_number = self.class_room_number_entry.get()

        if len(class_room_number) == 0:
            messagebox.showwarning('Warning', 'Class room number cannot be blank.')

        elif not class_room_number.isdigit():
            messagebox.showwarning('Warning', 'Class room number should be numeric.')

        else:
            new_class = SdbmsClass()
            new_class.class_room_number = class_room_number
            self.__parent.sdbms_core.add_class(new_class)
            self.__parent.class_list_updater()
            self.__parent.deiconify()
            self.destroy()

    def on_add_class_closing(self):
        """ Will be called with Add Class is closed. """
        self.__parent.deiconify()
        self.destroy()
