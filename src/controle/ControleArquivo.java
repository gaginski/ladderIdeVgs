/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import modelo.Programacao;
import modelo.Configuracoes;
import org.json.JSONException;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import visao.FrmEditorComandos;

/**
 *
 * @author Vitor
 */
public class ControleArquivo {

    @SuppressWarnings("null")

    public boolean salvaProg(JSONObject prog, File diretorio, String nomeProjeto) throws IOException, JSONException, FileNotFoundException, ParseException {
          try (FileWriter prog_json = new FileWriter(diretorio +"/"+nomeProjeto+".json")) {
            prog_json.write(prog.toString());
        }
        
        System.out.println("Programação salva com sucesso!");
        return true;
    }
    // IMPORTANTE - REFORMULAR, COLOCAR NO CONTROLEARQUIVO
    private File pegaDiretorio(File diretorioProjeto ) {
        boolean verifica = false;

        JFileChooser fc = new JFileChooser();
        fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        int res = fc.showOpenDialog(null);

        if (res == JFileChooser.APPROVE_OPTION) {
            verifica = true;
            File diretorio = new File(fc.getSelectedFile().getAbsolutePath());
            diretorioProjeto = diretorio;
        }
        return diretorioProjeto;

    }
 // IMPORTANTE - REFORMULAR, COLOCAR NO CONTROLEARQUIVO
    /* public void salva(boolean novoDiretorio) {

        JSONObject progSalva = new JSONObject();
        progSalva = geraJsonSalvar();
        ControleArquivo cArquivo = new ControleArquivo();
        boolean verificaDiretorio = false;

        if (diretorioProjeto == null || novoDiretorio) {
            verificaDiretorio = pegaDiretorio();
        } else {
            verificaDiretorio = true;
        }
        if (verificaDiretorio) {
            cArquivo.salvaProg(progSalva, diretorioProjeto, nomeProjeto);
            JOptionPane.showMessageDialog(null, "Salvo com sucesso!");

        } else {
            JOptionPane.showMessageDialog(null, "Diretório não selecionado!");
        }
    }*/
}
