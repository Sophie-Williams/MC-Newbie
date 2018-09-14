void Interface :: loop(){
fd_set nefds, fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    bool finished =false;
    while(!finished){
        nefds = fds;
        int retval = select(1, &nefds, NULL, NULL, NULL);
        if (retval == -1)
            perror("select()");
        else if (retval){
            m.get(0);
            handle();
        }
        else{ //Timeout
            ERROR_MESSAGE("Invalid Timeout performed by select.");
        }
    }
}

void Interface :: handle(){
    if(m.from() == ID_GAME_MANAGER){
        if(m.isTest()){
            m.testResponse();
            m.send(1);
        }
        //TODO MANAGE MESSAGE FROM GM
    }else{
        //MANAGE MESSAGE FROM BOT
        handler(m);
    }
}

