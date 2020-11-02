package com.example.RobotDoWydawaniaLekow;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class Activity2 extends AppCompatActivity {
    DatabaseReference reff;
    ListView listView1;
    ArrayList<String> arrayList = new ArrayList<>();
    String dzien;
    String miesiac;
    String rok;
    String godziny;
    String minuty;
    Long ilosc;
    String temp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);

        // ustawianie tytułu i strzałki powrotu
        getSupportActionBar().setTitle(getString(R.string.full_list));
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // łączenie z bazą i zczytanie z niej danych
        reff = FirebaseDatabase.getInstance().getReference().child("Dane");
        reff.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                ilosc = snapshot.getChildrenCount()-1;
                for(long i = ilosc.longValue(); i > ilosc-20 && i > 0; --i){
                    temp = "" + i;
                    dzien = snapshot.child("dane" + temp).child("dzien").getValue().toString();
                    miesiac = snapshot.child("dane" + temp).child("miesiac").getValue().toString();
                    rok = snapshot.child("dane" + temp).child("rok").getValue().toString();
                    godziny = snapshot.child("dane" + temp).child("godziny").getValue().toString();
                    minuty = snapshot.child("dane" + temp).child("minuty").getValue().toString();
                    if(miesiac.length()==1)
                        miesiac = "0"+miesiac;
                    if(minuty.length()==1)
                        minuty = "0"+minuty;
                    dodajNaListe();
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });


    }

    // dodanie zczytanych elementów na listę
    public void dodajNaListe() {
        listView1 = (ListView) findViewById(R.id.listview1);
        arrayList.add(dzien+"."+miesiac+"."+rok+", "+godziny+":"+minuty);
        //Log.d("nanana", "-------------------------");
        ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, arrayList);
        listView1.setAdapter(arrayAdapter);
    }
}