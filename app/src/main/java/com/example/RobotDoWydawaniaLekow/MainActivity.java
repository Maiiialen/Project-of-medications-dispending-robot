package com.example.RobotDoWydawaniaLekow;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    DatabaseReference reff;
    DatabaseReference reffUstawienia;
    String iloscPozostalychDawek;
    TextView iloscDawek;
    ListView listView;
    ArrayList<String> arrayList = new ArrayList<>();
    Button fullList;
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
        setContentView(R.layout.activity_main);

        //przypisanie przycisku do zmiennej
        fullList = (Button) findViewById(R.id.button_fullList);
        iloscDawek = (TextView) findViewById(R.id.textiloscDawek);

        // ustawianie tytułu
        getSupportActionBar().setTitle(getString(R.string.mainPage));

        // łączenie z bazą i zczytanie z niej danych
        reffUstawienia = FirebaseDatabase.getInstance().getReference().child("Ustawienia");
        reffUstawienia.addValueEventListener(new ValueEventListener() {
             @Override
             public void onDataChange(@NonNull DataSnapshot snapshot) {
                 try{
                    iloscPozostalychDawek = snapshot.child("iloscPozostalychDawek").getValue().toString();
                 } catch (Exception e) {}
                 dodajIloscDawek();
             }

             @Override
                public void onCancelled(@NonNull DatabaseError error) {}
         });

        reff = FirebaseDatabase.getInstance().getReference().child("Dane");
        reff.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                ilosc = snapshot.getChildrenCount();
                for(long i = ilosc.longValue(); i > ilosc-3; --i){
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
            public void onCancelled(@NonNull DatabaseError error) {}
        });

        fullList.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openActivity1();
            }
        });
    }

    // obsuguje przechodzenie do innych kart z przycisków ukrytych pod "3 kropkami" w prawym górnym rogu
    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        if(item.getItemId() == R.id.settings){
            openActivity();
        }
        return super.onOptionsItemSelected(item);
    }

    public void openActivity(){
        Intent intent = new Intent(this, Activity1.class);
        startActivity(intent);
    }

    public void openActivity1(){
        Intent intent = new Intent(this, Activity2.class);
        startActivity(intent);
    }

    // utworzenie "3 kropek" w prawym górnym rogu i ich funkcjonalności
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.my_menu, menu);
        return true;
    }

    // dodanie zczytanych elementów na listę
    public void dodajNaListe() {
        listView = (ListView) findViewById(R.id.listview);
        arrayList.add(dzien+"."+miesiac+"."+rok+", "+godziny+":"+minuty);
        //Log.d("nanana", "-------------------------");
        ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, arrayList);
        listView.setAdapter(arrayAdapter);
    }

    // dodanie zczytanych elementów na listę
    public void dodajIloscDawek() {
        iloscDawek.setText(iloscPozostalychDawek + "/14");
    }
}