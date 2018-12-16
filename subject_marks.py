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
