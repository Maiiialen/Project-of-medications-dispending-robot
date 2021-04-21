package com.example.RobotDoWydawaniaLekow;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class Activity1 extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    DatabaseReference reff;
    Przesyl_ustawien przesyl_ustawien;
    Button buttonSave;
    Button buttonUzupelnienie;
    String liczbaPozostalychDawek;
    Integer Dawek;
    TextView liczbaDawek;
    String liczba;
    String godziny1;
    String godziny2;
    String godziny3;
    Spinner spinerDawki;
    Spinner spinerGodziny1;
    Spinner spinerGodziny2;
    Spinner spinerGodziny3;
    ArrayAdapter<CharSequence> adapter_dawki;
    ArrayAdapter<CharSequence> adapter_godziny1;
    ArrayAdapter<CharSequence> adapter_godziny2;
    ArrayAdapter<CharSequence> adapter_godziny3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_1);

        // ustawianie tytułu i strzałki powrotu
        getSupportActionBar().setTitle(getString(R.string.settings));
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // przypisanie do zmiennych istniejących obiektów w oknie
        buttonSave = (Button) findViewById(R.id.buttonSave);
        buttonUzupelnienie = (Button) findViewById(R.id.buttonUzupelnienie);
        spinerDawki = findViewById(R.id.spinner_dawki);
        spinerGodziny1 = findViewById(R.id.spinner_godzina1);
        spinerGodziny2 = findViewById(R.id.spinner_godzina2);
        spinerGodziny3 = findViewById(R.id.spinner_godzina3);
        liczbaDawek = (TextView) findViewById(R.id.textViewliczbaDawek);

        // utworzenie adapterów
        adapter_dawki = ArrayAdapter.createFromResource(this, R.array.liczba, android.R.layout.simple_spinner_item);
        adapter_dawki.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        adapter_godziny1 = ArrayAdapter.createFromResource(this, R.array.godziny, android.R.layout.simple_spinner_item);
        adapter_godziny1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        adapter_godziny2 = ArrayAdapter.createFromResource(this, R.array.godziny, android.R.layout.simple_spinner_item);
        adapter_godziny2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        adapter_godziny3 = ArrayAdapter.createFromResource(this, R.array.godziny, android.R.layout.simple_spinner_item);
        adapter_godziny3.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        // przyppisanie adapterów do spinerów i ustawienie wartości początkowych
        spinerDawki.setAdapter(adapter_dawki);
        spinerDawki.setOnItemSelectedListener(this);
        spinerGodziny1.setAdapter(adapter_godziny1);
        spinerGodziny1.setOnItemSelectedListener(this);
        spinerGodziny2.setAdapter(adapter_godziny2);
        spinerGodziny2.setOnItemSelectedListener(this);
        spinerGodziny3.setAdapter(adapter_godziny3);
        spinerGodziny3.setOnItemSelectedListener(this);

        // łączenie z bazą danych i zczytanie z bazy zapisanych ustawień
        przesyl_ustawien = new Przesyl_ustawien();
        reff = FirebaseDatabase.getInstance().getReference().child("Ustawienia");
        reff.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String text;
                try {
                    liczbaPozostalychDawek = snapshot.child("liczbaPozostalychDawek").getValue().toString();
                    liczba = snapshot.child("liczba").getValue().toString();
                    godziny1 = snapshot.child("godziny1").getValue().toString();
                    godziny2 = snapshot.child("godziny2").getValue().toString();
                    godziny3 = snapshot.child("godziny3").getValue().toString();
                } catch (Exception e) {}
                ustawUstawienia();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        // zapisanie nowych ustawień do bazy danych wywoływane po naciśnięciu przycisku
        buttonSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String text;
                Dawek = Integer.parseInt(liczbaPozostalychDawek);

                text = spinerDawki.getSelectedItem().toString();
                int liczba = Integer.parseInt(text.trim());
                przesyl_ustawien.setLiczba(liczba);
                reff.setValue(przesyl_ustawien);

                text = spinerGodziny1.getSelectedItem().toString();
                przesyl_ustawien.setGodziny1(text);
                reff.setValue(przesyl_ustawien);

                text = spinerGodziny2.getSelectedItem().toString();
                przesyl_ustawien.setGodziny2(text);
                reff.setValue(przesyl_ustawien);

                text = spinerGodziny3.getSelectedItem().toString();
                przesyl_ustawien.setGodziny3(text);
                reff.setValue(przesyl_ustawien);

                przesyl_ustawien.setLiczbaPozostalychDawek(Dawek);
                reff.setValue(przesyl_ustawien);

                Toast.makeText(view.getContext(), "Ustawione.", Toast.LENGTH_SHORT).show();
            }
        });

        // zapisanie nowych ustawień do bazy danych wywoływane po naciśnięciu przycisku
        buttonUzupelnienie.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
            String text;
            Dawek = 15;
            liczbaPozostalychDawek = Dawek.toString();

            text = spinerDawki.getSelectedItem().toString();
            int liczba = Integer.parseInt(text.trim());
            przesyl_ustawien.setLiczba(liczba);
            reff.setValue(przesyl_ustawien);

            text = spinerGodziny1.getSelectedItem().toString();
            przesyl_ustawien.setGodziny1(text);
            reff.setValue(przesyl_ustawien);

            text = spinerGodziny2.getSelectedItem().toString();
            przesyl_ustawien.setGodziny2(text);
            reff.setValue(przesyl_ustawien);

            text = spinerGodziny3.getSelectedItem().toString();
            przesyl_ustawien.setGodziny3(text);
            reff.setValue(przesyl_ustawien);

            przesyl_ustawien.setLiczbaPozostalychDawek(Dawek);
            reff.setValue(przesyl_ustawien);

            Toast.makeText(view.getContext(), "Ustawione.", Toast.LENGTH_SHORT).show();
            }
        });
    }

    // zapisanie w spinerach wartości zczytach z bazy
    public void ustawUstawienia() {
        spinerDawki.setSelection(adapter_dawki.getPosition(liczba));
        spinerGodziny1.setSelection(adapter_godziny1.getPosition(godziny1));
        spinerGodziny2.setSelection(adapter_godziny2.getPosition(godziny2));
        spinerGodziny3.setSelection(adapter_godziny3.getPosition(godziny3));
        liczbaDawek.setText(liczbaPozostalychDawek + "/15");
    }

    public void openActivity1(){
        Intent intent = new Intent(this, Activity2.class);
        startActivity(intent);
    }

    // wykonuje się gdy w spinerze zmieni się wartość
    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }
}