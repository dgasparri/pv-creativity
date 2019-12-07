# Reading an excel file using Python 
import xlrd 
  
# Give the location of the file 
loc = ("./data.xlsx") 
  
# To open Workbook 
wb = xlrd.open_workbook(loc) 
sheet = wb.sheet_by_index(0) 

print(sheet.cell_value(0, 3))
print(sheet.cell_value(3, 0))
# For row 0 and column 0
#day 1 -> row 2 -> rowDay+1 (iniziano da zero)
#colHour [9-18] -> col 2 (C) -> colHour -7
f = open("./data.txt", "w")
for rowDay in range(1,365+1):
    for colHour in range(9, 18+1):
        W = sheet.cell_value(rowDay+1, colHour-7)
        print(rowDay, colHour, W, sep=",", end="\n")
        f.write("{} {} {}\n".format(rowDay, colHour, W))
    # You need a blank line every time the x value changes.
    f.write("\n".format(rowDay, colHour, W))

f.close()