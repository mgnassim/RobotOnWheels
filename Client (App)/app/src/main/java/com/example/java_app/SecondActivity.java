package com.example.java_app;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Base64;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class SecondActivity extends AppCompatActivity {

    Thread Thread1 = null;
    Thread UDP = null;
    int level = 0;
    String IP_ADDRESS = "172.20.10.10";
    int CAMERA_PORT = 51000;
    int SERVER_PORT = 8000;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        getSupportActionBar().hide();

        upKey();
        downKey();
        leftKey();
        rightKey();
        sirenSwitch();
        shootPump();
        servoUpKey();
        servoDownKey();

        Button btnConnect = findViewById(R.id.connect);
        btnConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Thread1 = new Thread(new Connection());
                Thread1.start();
            }
        });

        Button btnCamera = findViewById(R.id.cameraBtn);
        btnCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                UDP = new Thread(new UDP());
                UDP.start();
            }
        });
    }

    class UDP implements Runnable {
        public void run() {
            try {
                InetAddress address = InetAddress.getByName(IP_ADDRESS);
                DatagramSocket socket = new DatagramSocket();

                while (true) {

                    DatagramPacket request = new DatagramPacket(new byte[1], 1, address, CAMERA_PORT);
                    socket.send(request);

                    byte[] buffer = new byte[65536];
                    DatagramPacket response = new DatagramPacket(buffer, buffer.length);
                    socket.receive(response);

                    String jpgBase64 = new String(buffer, 0, response.getLength());

                    ImageView imageView = findViewById(R.id.liveVideo);

                    runOnUiThread(new Runnable() {
                        @SuppressLint("SetTextI18n")
                        @Override
                        public void run() {
                            imageView.setImageBitmap(decodeBase64StringToBitmap(jpgBase64));
                        }
                    });

                    System.out.println(jpgBase64 + '\n');

                }

            } catch (SocketTimeoutException ex) {
                System.out.println("Timeout error: " + ex.getMessage());
                ex.printStackTrace();
            } catch (IOException ex) {
                System.out.println("Client error: " + ex.getMessage());
                ex.printStackTrace();
            }
        }

        public Bitmap decodeBase64StringToBitmap(String base64Message) {
            byte[] imageBytes = Base64.decode(base64Message, Base64.DEFAULT);
            Bitmap decodedByte = BitmapFactory.decodeByteArray(imageBytes, 0, imageBytes.length);

            if (decodedByte != null) {
                System.out.println("Decoded Bitmap is niet null.\n");
            }

            if (decodedByte == null) {
                System.out.println("Decoded Bitmap is WEL null!");
            }

            return decodedByte;
        }

    }

    private PrintWriter output, output2;
    private BufferedReader input, input2;
    Socket socket, socket2;

    class Connection implements Runnable {
        public void run() {
            try {
                socket = new Socket(IP_ADDRESS, SERVER_PORT);
                socket2 = new Socket(IP_ADDRESS, 8001);
                output = new PrintWriter(socket.getOutputStream());
                input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                output2 = new PrintWriter(socket2.getOutputStream());
                input2 = new BufferedReader(new InputStreamReader(socket2.getInputStream()));
                runOnUiThread(new Runnable() {
                    @SuppressLint("SetTextI18n")
                    @Override
                    public void run() {
                        System.out.println("Connected\n");
                    }
                });
                new Thread(new Receive()).start();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    class Receive implements Runnable {
        @Override
        public void run() {
            while (true) {
                try {
                    final String message = input.readLine();
                    // [0] = temperature, [1] = distance, [2] = rpm of m/s, [3] = orientation/compass, [4] = waterlevel
                    String[] sensorData = message.split(" ");
                    if (message != null) {
                        runOnUiThread(new Runnable() {
                            @SuppressLint("SetTextI18n")
                            @Override
                            public void run() {
                                System.out.println("message received is: " + message);
                                TextView temperatureSensor = findViewById(R.id.txt_drive_temperature);
                                TextView distanceSensor = findViewById(R.id.txt_drive_distance);
                                TextView rpmSensor = findViewById(R.id.txt_drive_speed);
                                TextView compassSensor = findViewById(R.id.txt_drive_compass);
//                                TextView waterLevelSensor = findViewById(R.id.txt_drive_water);

                                temperatureSensor.setText(sensorData[0] + "°C");
                                distanceSensor.setText(sensorData[1] + " cm");
                                rpmSensor.setText(sensorData[2] + " m/s");
                                compassSensor.setText(sensorData[3]);
//                                waterLevelSensor.setText("Waterlevel: " + sensorData[4]);
                            }
                        });
                    } else {
                        Thread1 = new Thread(new Connection());
                        Thread1.start();
                        return;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    class Send implements Runnable {
        private String message;

        Send(String message) {
            this.message = message;
        }

        @Override
        public void run() {
            if(message.equals("o") || message.equals("l")) { // server of the servo
                output2.write(message);
                output2.flush();
            } else {
                output.write(message); // all else
                output.flush();
            }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    System.out.println("sent message: " + message);
                }
            });
        }
    }

    @SuppressLint("ClickableViewAccessibility")
    public void shootPump() {
        Button up_key = findViewById(R.id.shootPump);
        up_key.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Send("z"));
                        thread.start();
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Send("x"));
                        thread.start();
                        return true;
                }
                return false;
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

    public void servoUpKey() {
        Button servoUpKey = findViewById(R.id.servoUp);
        servoUpKey.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                level++;
                Thread thread = new Thread(new Send("o"));
                thread.start();
                if (level >= 2) {
                    level = 2;
                    showAlertDialog("Unable to aim watergun higher.");
                }
            }
        });
    }

    public void servoDownKey() {
        Button servoDownKey = findViewById(R.id.servoDown);
        servoDownKey.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                level--;
                Thread thread = new Thread(new Send("l"));
                thread.start();
                if (level <= -2) {
                    level = -2;
                    showAlertDialog("Unable to aim watergun lower.");
                }
            }
        });
    }

    public void sirenSwitch() {
        @SuppressLint("UseSwitchCompatOrMaterialCode")
        Switch siren = findViewById(R.id.sirenSwitch);
        siren.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (siren.isChecked()) {
                    Thread thread = new Thread(new Send("b"));
                    thread.start();
                } else {
                    Thread thread = new Thread(new Send("v"));
                    thread.start();
                }
            }
        });
    }

    @SuppressLint("ClickableViewAccessibility")
    public void upKey() {
        Button up_key = findViewById(R.id.btn_drive_frwrds);
        up_key.setOnTouchListener(new View.OnTouchListener() {
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Send("w"));
                        thread.start();
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Send("q"));
                        thread.start();
                        return true;
                }
                return false;
            }
        });
    }

    @SuppressLint("ClickableViewAccessibility")
    public void downKey() {
        Button down_key = findViewById(R.id.btn_drive_bckwrds);
        down_key.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Send("s"));
                        thread.start();
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Send("q"));
                        thread.start();
                        return true;
                }
                return false;
            }
        });
    }

    @SuppressLint("ClickableViewAccessibility")
    public void leftKey() {
        Button left_key = findViewById(R.id.btn_drive_Left);
        left_key.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Send("d"));
                        thread.start();
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Send("q"));
                        thread.start();
                        return true;
                }
                return false;
            }
        });
    }

    @SuppressLint("ClickableViewAccessibility")
    public void rightKey() {
        Button right_key = findViewById(R.id.btn_drive_right);
        right_key.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        Thread thread = new Thread(new Send("a"));
                        thread.start();
                        return true;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        thread = new Thread(new Send("q"));
                        thread.start();
                        return true;
                }
                return false;
            }
        });
    }
}
