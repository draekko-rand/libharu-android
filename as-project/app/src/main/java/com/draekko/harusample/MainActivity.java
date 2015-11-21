package com.draekko.harusample;

import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.draekko.libharu.Pdf;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private ProgressDialog pDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button makepdf = (Button)findViewById(R.id.button);
        makepdf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                pDialog = new ProgressDialog(MainActivity.this);
                pDialog.setMessage("Working");
                pDialog.setIndeterminate(true);
                pDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
                pDialog.setCancelable(false);
                pDialog.show();

                new AsyncMakePdf().execute();
            }
        });
    }

    class AsyncMakePdf extends AsyncTask<Void, Void, Void> {

        boolean status = true;

        @Override
        protected Void doInBackground(Void... params) {
            Pdf pdf = new Pdf(MainActivity.this);
            status = pdf.samplePdf(Environment.getExternalStorageDirectory().getAbsolutePath(), "sample.pdf");
            return null;
        }

        @Override
        protected void onPostExecute(Void p) {
            String statusString;
            if (status) {
                statusString = "PDF was created in " + Environment.getExternalStorageDirectory().getAbsolutePath() + " as sample.pdf";
            } else {
                statusString = "PDF wasn't created";
            }
            Toast.makeText(MainActivity.this, statusString, Toast.LENGTH_LONG).show();
            pDialog.cancel();
        }
    }
}
