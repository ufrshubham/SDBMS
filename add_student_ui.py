from tkinter import *
from tkinter import messagebox

from student import Student
from subject_marks import SubjectMarks


class AddStudentUI(Tk):
    """ This class creates the GUI for 'Add Student' menu option. """

    def __init__(self, selected_class, parent):
        super().__init__()
        self.__selected_class = selected_class
        self.__parent = parent
        self.__parent.withdraw()

        self.title('Add new student')
        self.geometry('250x200')
        self.resizable(0, 0)

        self.details_frame = Frame(master=self)
        self.details_frame.pack(side=TOP)

        self.label_frame = Frame(master=self.details_frame)
        self.entry_frame = Frame(master=self.details_frame)
        self.label_frame.pack(side=LEFT)
        self.entry_frame.pack(side=RIGHT)

        self.name_label = Label(master=self.label_frame, text='Name')
        self.roll_number_label = Label(master=self.label_frame, text='Roll number')
        self.name_label.pack()
        self.roll_number_label.pack()

        self.name_entry = Entry(master=self.entry_frame)
        self.roll_number_entry = Entry(master=self.entry_frame)
        self.name_entry.pack()
        self.roll_number_entry.pack()

        self.marks_frame = LabelFrame(master=self, text='Subject Marks')
        self.marks_frame.pack(side=BOTTOM, fill=X)
        self.marks_label_frame = Frame(master=self.marks_frame)
        self.marks_entry_frame = Frame(master=self.marks_frame)
        self.marks_label_frame.pack(side=LEFT)
        self.marks_entry_frame.pack()

        self.english_label = Label(master=self.marks_label_frame, text='English')
        self.physics_label = Label(master=self.marks_label_frame, text='Physics')
        self.chemistry_label = Label(master=self.marks_label_frame, text='Chemistry')
        self.maths_label = Label(master=self.marks_label_frame, text='Maths')
        self.computer_science_label = Label(master=self.marks_label_frame, text='Computer Science')

        self.english_entry = Entry(master=self.marks_entry_frame)
        self.physics_entry = Entry(master=self.marks_entry_frame)
        self.chemistry_entry = Entry(master=self.marks_entry_frame)
        self.maths_entry = Entry(master=self.marks_entry_frame)
        self.computer_science_entry = Entry(master=self.marks_entry_frame)

        self.english_label.pack()
        self.physics_label.pack()
        self.chemistry_label.pack()
        self.maths_label.pack()
        self.computer_science_label.pack()
        self.english_entry.pack()
        self.physics_entry.pack()
        self.chemistry_entry.pack()
        self.maths_entry.pack()
        self.computer_science_entry.pack()

        create_button = Button(master=self, text='Add', command=self.on_add_clicked)
        create_button.pack()

        self.protocol("WM_DELETE_WINDOW", self.on_add_student_closing)
        self.mainloop()

    def on_add_clicked(self):
        """ This method will be called when Add button is clicked. """
        name = self.name_entry.get()
        roll_number = self.roll_number_entry.get()
        english = self.english_entry.get()
        physics = self.physics_entry.get()
        chemistry = self.chemistry_entry.get()
        maths = self.maths_entry.get()
        comp_sci = self.computer_science_entry.get()

        if len(name) == 0:
            messagebox.showwarning('Warning', 'Student name cannot be empty.')
        elif len(roll_number) == 0 :
            messagebox.showwarning('Warning', 'Student roll number cannot be empty.')
        elif len(english) == 0:
            messagebox.showwarning('Warning', 'English marks cannot be empty.')
        elif len(physics) == 0:
            messagebox.showwarning('Warning', 'Physics marks cannot be empty.')
        elif len(chemistry) == 0:
            messagebox.showwarning('Warning', 'Chemistry marks cannot be empty.')
        elif len(maths) == 0:
            messagebox.showwarning('Warning', 'Maths marks cannot be empty.')
        elif len(comp_sci) == 0:
            messagebox.showwarning('Warning', 'Computer Science marks cannot be empty.')
        elif not roll_number.isdigit():
            messagebox.showwarning('Warning', 'Roll number should be numeric.')
        elif not (english.isdigit() and physics.isdigit() and chemistry.isdigit() and
                  maths.isdigit() and comp_sci.isdigit()):
            messagebox.showwarning('Warning', 'Marks should be numeric.')
        else:
            subject_marks = SubjectMarks()
            subject_marks.english = english
            subject_marks.physics = physics
            subject_marks.chemistry = chemistry
            subject_marks.maths = maths
            subject_marks.computer_science = comp_sci

            new_student = Student()
            new_student.marks = subject_marks
            new_student.name = name
            new_student.roll_number = roll_number

            self.__selected_class.add_student(new_student)
            self.__parent.student_list_updater(self.__selected_class.class_room_number)
            self.__parent.deiconify()
            self.destroy()

    def on_add_student_closing(self):
        """ Will be called when Add Student is closed. """
        self.__parent.deiconify()
        self.destroy()
