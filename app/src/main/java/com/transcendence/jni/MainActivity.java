package com.transcendence.jni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import com.transcendence.jni.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jni' library on application startup.
    static {
        System.loadLibrary("jni");
    }

    public native String stringFromJNI();

    public native void changeName();   //alt + enter 创建   改变我们的属性 name

    public static native void changeAge();

    private String name = "joephone";    //调用C++ 修改为 joe

    public static int age = 28;   //  用native代码 修改为：29

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        Button btnChangeName = binding.btnChangeName;
        btnChangeName.setOnClickListener(v -> {
            System.out.println("修改前的name:"+name);
            changeName();
            System.out.println("修改后的name:"+name);
            btnChangeName.setText("修改后的name:"+name);
        });

        Button btnChangeAge = binding.btnChangeAge;
        btnChangeAge.setOnClickListener(v -> {
            System.out.println("修改前的age:"+age);
            changeAge();
            System.out.println("修改后的age:"+age);
            btnChangeAge.setText("修改后的age:"+age);
        });

    }



}