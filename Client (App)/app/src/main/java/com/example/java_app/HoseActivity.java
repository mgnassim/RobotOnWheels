package com.example.java_app;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class HoseActivity extends AppCompatActivity {

    Thread Thread1 = null;
    int level = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hose);
        getSupportActionBar().hide();

        Button btnConnect2 = findViewById(R.id.btn_hose_Start);
        btnConnect2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Thread1 = new Thread(new Thread1());
                Thread1.start();
            }
        });

        rightKey();
        leftKey();
        servoDownKey();
        servoUpKey();
        sirenSwitch();
    }

    public void sirenSwitch() {
        @SuppressLint("UseSwitchCompatOrMaterialCode")
        Switch siren = findViewById(R.id.sirenSwitch2);
        siren.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (siren.isChecked()) {
                    Thread thread = new Thread(new Thread3("b"));
                    thread.start();
                } else {
                    Thread thread = new Thread(new Thread3("v"));
                    thread.start();
                }
            }
        });
    }

    public void switchMode(View view) {
        Intent intent = new Intent(this, SecondActivity.class);
        startActivity(intent);
        System.out.println("Going to Motor control mode");
    }

    private PrintWriter output;
    private BufferedReader input;

    class Thread1 implements Runnable {
        public void run() {
            Socket socket;
            try {
                socket = new Socket("172.20.10.10", 8000);
                output = new PrintWriter(socket.getOutputStream());
                input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                runOnUiThread(new Runnable() {
                    @SuppressLint("SetTextI18n")
                    @Override
                    public void run() {
                        System.out.println("Connected\n");
                    }
                });
                new Thread(new Thread2()).start();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    class Thread2 implements Runnable {
        @Override
        public void run() {
            while (true) {
                try {
                    final String message = input.readLine();
                    if (message != null) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
//                                TextView distanceSensor = findViewById(R.id.txt_drive_distance);
//                                distanceSensor.setText("Distance: " + message);
                                System.out.println("Got message!");
                            }
                        });
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class Thread3 implements Runnable {
        private String message;

        Thread3(String message) {
            this.message = message;
        }

        @Override
        public void run() {
            output.write(message);
            output.flush();
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    System.out.println("sent message: " + message);
                }
            });
        }
    }

    public void servoUpKey() {
        Button servoUpKey = findViewById(R.id.btn_hose_up);
        servoUpKey.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                level++;
                Thread thread = new Thread(new Thread3("o"));
                thread.start();
                if(level >= 2) {
                    level = 2;
                    showAlertDialog("Unable to aim watergun higher.");
                }
            }
        });
    }

    public void servoDownKey() {
        Button servoDownKey = findViewById(R.id.btn_hose_Down);
        servoDownKey.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                level--;
                Thread thread = new Thread(new Thread3("l"));
                thread.start();
                if(level <= -2) {
                    level = -2;
                    showAlertDialog("Unable to aim watergun lower.");
                }
            }
        });
    }

    public void showAlertDialog(String directionWarning) {
        AlertDialog.Builder alert = new AlertDialog.Builder(this);
        alert.setTitle("Warning");
        alert.setMessage(directionWarning);
        alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
            }
        });
        alert.create().show();
    }

    @SuppressLint("ClickableViewAccessibility")
    public void leftKey() {
        Button toMotor = findViewById(R.id.btn_toMotor);
        Button left_key = findViewById(R.id.btn_drive_left2);
        left_key.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Thread3("d"));
                        thread.start();
                        toMotor.setEnabled(false);
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Thread3("q"));
                        thread.start();
                        toMotor.setEnabled(true);
                        return true;
                }
                return false;
            }
        });
    }

    @SuppressLint("ClickableViewAccessibility")
    public void rightKey() {
        Button toMotor = findViewById(R.id.btn_toMotor);
        Button right_key = findViewById(R.id.btn_drive_right2);
        right_key.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Thread3("a"));
                        thread.start();
                        toMotor.setEnabled(false);
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Thread3("q"));
                        thread.start();
                        toMotor.setEnabled(true);
                        return true;
                }
                return false;
            }
        });
    }

    public void hoseStart(View view) {

        Button toMotor = findViewById(R.id.btn_toMotor);
        toMotor.setEnabled(false);
        Button hoseStart = findViewById(R.id.btn_hose_Start);
        hoseStart.setEnabled(false);
        Button hoseStop = findViewById(R.id.btn_hose_Stop);
        hoseStop.setEnabled(true);

        Button b = (Button) view;
        System.out.println("Hose " + b.getText());
    }

    public void hoseStop(View view) {

        Button toMotor = findViewById(R.id.btn_toMotor);
        toMotor.setEnabled(true);
        Button hoseStop = findViewById(R.id.btn_hose_Stop);
        hoseStop.setEnabled(false);
        Button hoseStart = findViewById(R.id.btn_hose_Start);
        hoseStart.setEnabled(true);

        Button b = (Button) view;
        System.out.println("Hose " + b.getText());
    }
}