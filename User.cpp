////
//// Created by gal on 20/12/2019.
////
//
//#include <algorithm>
//#include <sstream>
//#include "User.h"
//using namespace std;
//
//string User::replaceBracketsComma(string &str) {
//    //std::replace( s.begin(), s.end(), 'x', 'y'); // replace all 'x' to 'y'
//    replace(str.begin(), str.end(), '(', ' ');
//    replace(str.begin(), str.end(), ')', ' ');
//    replace(str.begin(), str.end(), '"', ' ');
//    replace(str.begin(), str.end(), ',', ' ');
//    replace(str.begin(), str.end(), '\t', ' ');
//    return str;
//}
//void User::split(string &str) {
//    stringstream token(str);
//    string intermediate;
//    string deleteVector = "";
//    // Tokenizing w.r.t. space ' '
//    while (getline(token, intermediate, ' ')) {
//        string tmp;
//        int i = 0;
//        for (int i = 0; i < str.length(); i++) {
//            if (str[i] == '=') {
//                string var = str.substr(0, str.find('=') - 1);
//                string op = str.substr(str.find('='), 1);
//                string s = str.substr(str.find('=') + 1, str.length());
//                string::iterator end_pos = std::remove(var.begin(), var.end(), ' ');
//                var.erase(end_pos, var.end());
//                string::iterator end_pos2 = std::remove(op.begin(), op.end(), ' ');
//                op.erase(end_pos2, op.end());
//                string::iterator end_pos3 = std::remove(s.begin(), s.end(), ' ');
//                s.erase(end_pos3, s.end());
//                data.push_back(var);
//                data.push_back(op);
//                data.push_back(s);
//                intermediate = "";
//            }
//            if(str[i] == '\t'){
//                replace(str.begin(), str.end(), '\t', ' ');
//            }
//        }
//        if(intermediate != ""){
//            data.push_back(intermediate);
//        }
//        //remove "" from the vector
//        auto itr = find(data.begin(), data.end(), deleteVector);
//        if (itr != data.end()) data.erase(itr);
//    }
//}
//void User::start(){
//    int index=0;
//    while (index<data.size()){
//        string datafinf=data.at(index);
//        Command* c=mappingCommand.at(datafinf);
//        if (c!=NULL){
//            index+= c->execute(index + 1, data);
//        }
//        if(datafinf=="openDataServer")
//        for (auto x : threads) {
//            pthread_join(x, NULL);
//        }
//    }
//}
////User::User(pthread_mutex_t * mutex,vector<pthread_t> *threads)
//User::User() {
//    userInitializeParameterMap();
//    simulatorInitializeParameterMap();
//    if (pthread_mutex_init(&mutex, NULL) != 0)
//    {
//        printf("mutex init failed");
//        return;
//    }
//    SymbolTable* symbolTable=new SymbolTable(simulator, user, &mutex);
//    mappingCommand.insert(make_pair("openDataServer", new OpenServerCommand(symbolTable,&threads)));
////    mappingCommand.insert(make_pair("connectControlClient", new ConnectCommand(symbolTable,threads)));
////    mappingCommand.insert(make_pair("var", new DefineVarCommand(symbolTable)));
//}
//void User::userInitializeParameterMap(){
//
//    //////user-map
//    user.push_back({"airspeed","/instrumentation/airspeed-indicator/indicated-speed-kt",0});
//    user.push_back({"heading-indicator_offset-deg","/instrumentation/heading-indicator/offset-deg",0});
//    user.push_back({"altimeter_altitude", "/instrumentation/altimeter/indicated-altitude-ft",0});
//    user.push_back({"altimeter_pressure","/instrumentation/altimeter/pressure-alt-ft",0});
//    user.push_back({"attiude_indicated-pitch","/instrumentation/attitude-indicator/indicated-pitch-deg",0});
//    user.push_back({"attiude_indicated-roll","/instrumentation/attitude-indicator/indicated-roll-deg",0});
//    user.push_back({"attiude_internal-pitch", "/instrumentation/attitude-indicator/internal-pitch-deg",0});
//    user.push_back({"attiude_internal-roll","/instrumentation/attitude-indicator/internal-roll-deg",0});
//    user.push_back({"encoder_indicated-altitude","/instrumentation/encoder/indicated-altitude-ft",0});
//    user.push_back({"encoder_pressure","/instrumentation/encoder/pressure-alt-ft",0});
//    user.push_back({"gps_indicated-altitude","/instrumentation/gps/indicated-altitude-ft",0});
//    user.push_back({"gps_indicated-ground-speed","/instrumentation/gps/indicated-ground-speed-kt",0});
//    user.push_back({"gps_indicated-vertical-speed","/instrumentation/gps/indicated-vertical-speed",0});
//    user.push_back({"heading","/instrumentation/heading-indicator/indicated-heading-deg",0});
//    user.push_back({"compass","/instrumentation/magnetic-compass/indicated-heading-deg",0});
//    user.push_back({"slip-skid-ball","/instrumentation/slip-skid-ball/indicated-slip-skid",0});
//    user.push_back({"turn_rate","/instrumentation/turn-indicator/indicated-turn-rate",0});
//    user.push_back({"vertical_speed_indicator","/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0});
//    user.push_back({"aileron","/controls/flight/aileron",0});
//    user.push_back({"elevator","/controls/flight/elevator",0});
//    user.push_back({"rudder","/controls/flight/rudder",0});
//    user.push_back({"flaps","/controls/flight/flaps",0});
//    user.push_back({"throttle","/controls/engines/current-engine/throttle",0});
//    user.push_back({"rpm","/engines/engine/rpm",0});
//}
//void User::simulatorInitializeParameterMap(){
//    /////////simulator-map
//    simulator.push_back({"airspeed","/instrumentation/airspeed-indicator/indicated-speed-kt",0});
//    simulator.push_back({"heading_offset","/instrumentation/heading-indicator/offset-deg",0});
//    simulator.push_back({"altimeter_altitude", "/instrumentation/altimeter/indicated-altitude-ft",0});
//    simulator.push_back({"altimeter_pressure","/instrumentation/altimeter/pressure-alt-ft",0});
//    simulator.push_back({"attiude_indicated-pitch","/instrumentation/attitude-indicator/indicated-pitch-deg",0});
//    simulator.push_back({"attiude_indicated-roll","/instrumentation/attitude-indicator/indicated-roll-deg",0});
//    simulator.push_back({"attiude_internal-pitch", "/instrumentation/attitude-indicator/internal-pitch-deg",0});
//    simulator.push_back({"attiude_internal-roll","/instrumentation/attitude-indicator/internal-roll-deg",0});
//    simulator.push_back({"encoder_indicated-altitude","/instrumentation/encoder/indicated-altitude-ft",0});
//    simulator.push_back({"encoder_pressure","/instrumentation/encoder/pressure-alt-ft",0});
//    simulator.push_back({"gps_indicated-altitude","/instrumentation/gps/indicated-altitude-ft",0});
//    simulator.push_back({"gps_indicated-ground-speed","/instrumentation/gps/indicated-ground-speed-kt",0});
//    simulator.push_back({"gps_indicated-vertical-speed","/instrumentation/gps/indicated-vertical-speed",0});
//    simulator.push_back({"heading","/instrumentation/heading-indicator/indicated-heading-deg",0});
//    simulator.push_back({"compass","/instrumentation/magnetic-compass/indicated-heading-deg",0});
//    simulator.push_back({"slip-skid-ball","/instrumentation/slip-skid-ball/indicated-slip-skid",0});
//    simulator.push_back({"turn_rate","/instrumentation/turn-indicator/indicated-turn-rate",0});
//    simulator.push_back({"vertical_speed_indicator","/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0});
//    simulator.push_back({"aileron","/controls/flight/aileron",0});
//    simulator.push_back({"elevator","/controls/flight/elevator",0});
//    simulator.push_back({"rudder","/controls/flight/rudder",0});
//    simulator.push_back({"flaps","/controls/flight/flaps",0});
//    simulator.push_back({"throttle","/controls/engines/current-engine/throttle",0});
//    simulator.push_back({"rpm","/engines/engine/rpm",0});
//}
