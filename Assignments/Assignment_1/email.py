class Email:
    def __init__(self, sender_category, subject_line, date):
        self.subject_line = subject_line
        self.date = date

        m, d, y = date.split("-") #got this syntax from chatgpt to easily reformat the date
        self.formatted_date = y + m + d # for comparing dates easily 

        self.sender_category = sender_category
        
        if self.sender_category == "Boss": #categorize each sender by number to easily compare
            self.priority_number = 5
        elif self.sender_category == "Subordinate":
            self.priority_number = 4
        elif self.sender_category == "Peer":
            self.priority_number = 3
        elif self.sender_category == "ImportantPerson":
            self.priority_number = 2
        elif self.sender_category == "OtherPerson":
            self.priority_number = 1
    
    def __lt__(self,other):
        if self.priority_number != other.priority_number: 
            return self.priority_number < other.priority_number #prioritize by lowest priority_number
        else:
            return self.formatted_date > other.formatted_date #if the sender is the same prioritize by earliest date
    
    def __str__(self): #prints the email information in a well-formatted manor
        return (f"\tSender: {self.sender_category}\n"
                f"\tSubject: {self.subject_line}\n"
                f"\tDate: {self.date}\n")