package com.example.RobotDoWydawaniaLekow;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class Activity1 extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    DatabaseReference reff;
    Przesyl_ustawien przesyl_ustawien;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_1);

        // ustawianie tytułu i strzałki powrotu
        getSupportActionBar().setTitle("Ustawienia");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // spiner dawki
        Spinner spiner = findViewById(R.id.spinner_dawki);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.ilosc, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spiner.setAdapter(adapter);
        spiner.setOnItemSelectedListener(this);

        // łączenie z bazą danych
        przesyl_ustawien = new Przesyl_ustawien();
        reff = FirebaseDatabase.getInstance().getReference().child("Przesyl_ustawien");
    }

    public void openActivity1(){
        Intent intent = new Intent(this, Activity2.class);
        startActivity(intent);
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
        String text = adapterView.getItemAtPosition(i).toString();

        // przesłanie danego ustawienia
        int ilosc = Integer.parseInt(text.trim());
        przesyl_ustawien.setIlosc(ilosc);
        reff.setValue(przesyl_ustawien);


        if(adapterView.getItemAtPosition(i).toString() == "1"){
            Toast.makeText(adapterView.getContext(), "Ustawione: " + text + " dawka dziennie", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(adapterView.getContext(), "Ustawione: " + text + " dawki dziennie", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }
}