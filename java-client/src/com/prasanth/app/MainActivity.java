package com.prasanth.app;

import android.app.Activity;
import android.util.Log;
import android.os.ServiceManager;
import android.os.Binder;
import com.prasanth.Demoservice.IDemoService;
import com.prasanth.Demoservice.IDemoServiceCallback;
import android.os.IBinder;
import android.os.Bundle;
import android.os.RemoteException;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import android.os.Handler;
import android.os.Message;

import android.widget.TextView;

import java.lang.ref.WeakReference;

public class MainActivity extends Activity {
    public static final String ACTION_Demo_STATE_CHANGED = "android.prasanth.intent.action.Demo_STATE_CHANGED";
    private TextView txt_status;
    // private StatusHandler handler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        txt_status = findViewById(R.id.txt_status);
        // handler = new StatusHandler(txt_status);

        loadService();

        IntentFilter filter = new IntentFilter(ACTION_Demo_STATE_CHANGED);
        registerReceiver(mReceiver, filter);

    }
    private void loadService(){
        try {
            IBinder b = ServiceManager.getService("Demo.nativeservice");
            if(b != null) {
                final IDemoService service = IDemoService.Stub.asInterface(b);
                if(service != null) {
                    // int result = service.OnLoad();
                    // Log.d("DemoSERVICE", "OnLoad " + result);
                    service.registerCallback(mCallback);
                   // updateText(result == 1 ? "Connected" : "Disconnected");
                    //handler.sendMessage(handler.obtainMessage(0,result,0));
                } else {
                    Log.d("DemoSERVICE", "MainActivity asInterface fail.");
                }
            } else {
                Log.d("DemoSERVICE", "MainActivity get native service fail.");
            }
        } catch(RemoteException e) {
            Log.d("DemoSERVICE", "ERROR:" + e.getMessage());
        }
    }

    private IDemoServiceCallback mCallback = new IDemoServiceCallback.Stub() {
        public void onDemoInputConnected() {
            Log.d("DemoSERVICECALLBACK", "Connected ");
            updateText("Connected");
            // handler.sendMessage(handler.obtainMessage(0,1,0));
        }
        public void onDemoInputDisconnected() {
            Log.d("DemoSERVICECALLBACK", "NotConnected ");
            updateText("Disconnected");
            // handler.sendMessage(handler.obtainMessage(0,0,0));
        }
    };

    private BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            boolean state = intent.getBooleanExtra("state", false);
            Log.d("TAG", "BroadcastReceiver: Demo " + (state ? "Connected" : "Disconnected"));
        }
    };
    
    private  void updateText(final String status){
        MainActivity.this.runOnUiThread(new Runnable() {
            public void run() { 
                Log.d("UI thread status", status); 
            }
        });
    }
    // private class StatusHandler extends Handler {
    //     private final WeakReference<TextView> weakTextView;

    //     StatusHandler(TextView textView) {
    //         weakTextView = new WeakReference<>(textView);
    //     }
    //     @Override
    //     public void handleMessage(Message msg) {
    //         TextView textView = weakTextView.get();
    //         textView.setText(msg.arg1 == 1 ? "Connected" : "Disconnected");
    //     }
    // }
}
