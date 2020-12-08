Goal of this project is train my own cascade classifier for face detection using OpenCV and Python. 

Features provided:

  ~neg.txt, pos.txt, pos.vec - corresponding files with positive and negative samples paths
  
  ~template matching.py - some additional code with template matching(wrote it to become confident in python)
  
  ~cascade/ -  folder with cascade file(cascade.xml) and files with each stage which was executed during the training

  ~cascade_utils.py - function, which creates neg.txt
  
Sources:

  ~negative samples - https://groups.csail.mit.edu/vision/datasets/ADE20K/
  
  ~positive samples - http://shuoyang1213.me/WIDERFACE/
  
Tutorials:

  ~ http://note.sonots.com/SciSoftware/haartraining.html#Modified (general information, many useful features and links provided here)

  ~ https://www.youtube.com/watch?v=KecMlLUuiE4&list=PL1m2M8LQlzfKtkKq2lK5xko4X-8EZzFPI (OpenCv in Python, but for Cascade Training you need 8th video)
  
  ~https://www.youtube.com/watch?v=oXlwWbU8l2o&t=6s&ab_channel=freeCodeCamp.org (this tutorial provides basic image processing techniques in OpenCV using Python. Would be useful,   if you want to work with this library not only for Cascade Training)
  
  ~ https://docs.google.com/document/d/1TndDcxJW5xJNIG5ldvu6nOjq6rl5w2gpkbth_u_I_m4/edit - decription file for some problems, arised during the project developing( in Ukrainian,     because was done like extra6 task for OOP course)
