package com.prasanth.demoservice;

import com.prasanth.demoservice.IDemoServiceCallback;

interface IDemoService {
    int OnLoad();

    void registerCallback(IDemoServiceCallback cb);
    void unregisterCallback();
}
