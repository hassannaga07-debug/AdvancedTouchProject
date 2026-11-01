package com.shop.lathe;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("lathe");
    }

    public native void nativeComputeAdvancedTouch(
            float startX, float startY,
            float targetX, float targetY,
            int[] outXArray, int[] outYArray, int steps);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnStart = findViewById(R.id.btnStart);
        TextView resultText = findViewById(R.id.resultText);

        btnStart.setOnClickListener(v -> {
            int steps = 25;
            int[] xArray = new int[steps];
            int[] yArray = new int[steps];

            try {
                nativeComputeAdvancedTouch(
                        100f, 500f, 100f, 200f,
                        xArray, yArray, steps);

                StringBuilder result = new StringBuilder("تم حساب المسار بنجاح:\n");
                for (int i = 0; i < steps; i++) {
                    result.append(i + 1)
                            .append(". X=")
                            .append(xArray[i])
                            .append("  Y=")
                            .append(yArray[i])
                            .append('\n');
                }
                resultText.setText(result.toString());
                Toast.makeText(this, "اكتمل حساب المسار", Toast.LENGTH_SHORT).show();
            } catch (Exception e) {
                Toast.makeText(this, "حدث خطأ أثناء الحساب", Toast.LENGTH_LONG).show();
            }
        });
    }
}
