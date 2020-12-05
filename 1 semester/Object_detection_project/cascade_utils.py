import os
from pathlib import Path


def generate_negative_description_file():
    # open the output file for writing. will overwrite all existing data in there
    with open('neg.txt', 'w') as f:

        
        for i in os.listdir('D:/ADE20K_2016_07_26/images/training'):
            
            if(i == "misc"):
                for filename in os.listdir('D:/ADE20K_2016_07_26/images/training/misc'):
                    if(Path('D:/ADE20K_2016_07_26/images/training/misc/' + filename).suffix == '.jpg'):
                        # print("kekw")
                        f.write('D:/ADE20K_2016_07_26/images/training/misc/' + filename + '\n')

            else:
                for j in os.listdir('D:/ADE20K_2016_07_26/images/training/' + i):
                    for filename in os.listdir('D:/ADE20K_2016_07_26/images/training/' + i + '/' + j):
                        if(Path('D:/ADE20K_2016_07_26/images/training/' + i + '/' + j + '/' + filename).suffix == '.jpg'):
                            # print("{} \n".format(k))
                            # k += 1
                            f.write('D:/ADE20K_2016_07_26/images/training/' + i + '/' + j + '/' + filename + '\n')



        f.close()                