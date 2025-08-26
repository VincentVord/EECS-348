class Email:
    def __init__(self, sender_category, subject_line, date):
        self.subject_line = subject_line
        self.date = date

        if self.sender_category == "Boss": #categorize each sender by number to easily compare
            self.sender_category == 5
        elif self.sender_category == "Subordinate":
            self.sender_category == 4
        elif self.sender_category == "Peer":
            self.sender_category == 3
        elif self.sender_category == "ImportantPerson":
            self.sender_category == 2
        elif self.sender_category == "OtherPerson":
            self.sender_category == 1
        self.sender_category = sender_category
    
    def __lt__(self,other):
        if self.sender_category != other.sender_category: 
            return self.sender_category < other.sender_category #prioritize by sender category
        return self.date < other.date #if the sender is the same prioritize by earliest date
    
    def __str__(self): #prints the email information in a well-formatted manor
        return (f"Sender: {self.sender_category}\n"
                f"Subject: {self.subject_line}\n"
                f"Date: {self.date}\n")