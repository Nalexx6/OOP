#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//12_Group_Large_Group_12_Group_Large_Group_12_31

int main() {

    std::ifstream in ("D:/WIDER_train/wider_face_split/wider_face_train_bbx_gt.txt");
    std::ofstream out ("D:/UniversityLabs/OOP/1 semester/Object_detection_project/pos.txt");
    if(!in.is_open())
        return 1;

    if(!out.is_open())
        return 1;

    std::string path, fixed_path, res, parameter;
    int faces_quant, sum = 0;
    while(!in.eof() && sum <= 7000){

        fixed_path = "";
        res = "D:/WIDER_train/images/";
        in >> path;
//        for(int i = 2; i < path.size(); i++){
//            if(path[i] != '-')
//                fixed_path += path[i];
//        }

        in >> faces_quant;
        sum += faces_quant;

        res += path + " " + std::to_string(faces_quant);

        for(int i = 0; i < faces_quant; i++){

            for(int j = 0; j < 10; j++){

                in >> parameter;
                if(j < 4)
                    res += " " + parameter;

            }

        }

        if(faces_quant == 0){

            for(int j = 0; j < 10; j++){

                in >> parameter;
                if(j < 4)
                    res += " " + parameter;

            }

        }

        if(faces_quant != 0 && faces_quant <= 5)
            out << res << "\n";
        else
            sum -= faces_quant;

    }

    std::cout << sum;
    return 0;
}
