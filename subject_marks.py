from sdbms_base_class import SdbmsBaseClass


class SubjectMarks(SdbmsBaseClass):
    """ This class will hold a dictionary of subject marks """

    def __init__(self):
        super().__init__()
        self.__subject_marks = {'English': 0,
                                'Physics': 0,
                                'Chemistry': 0,
                                'Maths': 0,
                                'Computer Science': 0}

    @property
    def marks(self):
        """ Getter for subject marks """
        return self.__subject_marks

    @marks.setter
    def marks(self, value):
        self.__subject_marks = value

    @property
    def english(self):
        return self.__subject_marks['English']

    @english.setter
    def english(self, value):
        self.__subject_marks['English'] = value

    @property
    def physics(self):
        return self.__subject_marks['Physics']

    @physics.setter
    def physics(self, value):
        self.__subject_marks['Physics'] = value

    @property
    def chemistry(self):
        return self.__subject_marks['Chemistry']

    @chemistry.setter
    def chemistry(self, value):
        self.__subject_marks['Chemistry'] = value

    @property
    def maths(self):
        return self.__subject_marks['Maths']

    @maths.setter
    def maths(self, value):
        self.__subject_marks['Maths'] = value

    @property
    def computer_science(self):
        return self.__subject_marks['Computer Science']

    @computer_science.setter
    def computer_science(self, value):
        self.__subject_marks['Computer Science'] = value
