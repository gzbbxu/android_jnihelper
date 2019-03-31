package com.zkk.demo;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("jnihelper-lib");
    }

    boolean threadFlag = true;
    int i = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread() {
                    @Override
                    public void run() {
//                        stringFromJNI();
                        /*while(threadFlag){
                            createData();
                        }*/

                    }
                }.start();
            }
        });
        TextView tv_create_data = findViewById(R.id.tv_create_data);
        tv_create_data.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                new Thread() {
                    @Override
                    public void run() {
                        while (threadFlag) {
                            createData();
                            SystemClock.sleep(1000);
                        }
                    }
                }.start();


            }
        });
        Log.i("zhouke_test", "MainActivity jni 开始调用");
        tv.setText("dfa");

        Log.i("zhouke_test", "MainActivity jni  结束调用");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void createData();

    public void callBack(String string) {
        Log.i("zhouke", "callBack >> " + string);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        threadFlag = false;
    }
}
