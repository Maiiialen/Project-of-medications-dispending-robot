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
    String iloscPozostalychDawek;
    String ilosc;
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
        spinerDawki = findViewById(R.id.spinner_dawki);
        spinerGodziny1 = findViewById(R.id.spinner_godzina1);
        spinerGodziny2 = findViewById(R.id.spinner_godzina2);
        spinerGodziny3 = findViewById(R.id.spinner_godzina3);

        // utworzenie adapterów
        adapter_dawki = ArrayAdapter.createFromResource(this, R.array.ilosc, android.R.layout.simple_spinner_item);
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
                    //Log.d("przed", "----------");
                    iloscPozostalychDawek = snapshot.child("iloscPozostalychDawek").getValue().toString();
                    ilosc = snapshot.child("ilosc").getValue().toString();
                    godziny1 = snapshot.child("godziny1").getValue().toString();
                    godziny2 = snapshot.child("godziny2").getValue().toString();
                    godziny3 = snapshot.child("godziny3").getValue().toString();
                    //Log.d("po", "----------"+godziny1);
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

                text = spinerDawki.getSelectedItem().toString();
                int ilosc = Integer.parseInt(text.trim());
                przesyl_ustawien.setIlosc(ilosc);
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

                przesyl_ustawien.setIloscPozostalychDawek(iloscPozostalychDawek);
                reff.setValue(przesyl_ustawien);

                Toast.makeText(view.getContext(), "Ustawione.", Toast.LENGTH_SHORT).show();
            }
        });
    }

    // zapisanie w spinerach wartości zczytach z bazy
    public void ustawUstawienia() {
        spinerDawki.setSelection(adapter_dawki.getPosition(ilosc));
        spinerGodziny1.setSelection(adapter_godziny1.getPosition(godziny1));
        spinerGodziny2.setSelection(adapter_godziny2.getPosition(godziny2));
        spinerGodziny3.setSelection(adapter_godziny3.getPosition(godziny3));
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