/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import br.pro.turing.javino.Javino;
import java.io.FileNotFoundException;
import java.io.IOException;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import modelo.Programacao;
import modelo.config;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.simple.parser.ParseException;
import visao.frmSelecionaPortas;

/**
 *
 * @author Vitor
 */
public class ControleComunicacao {

    Javino comunica = new Javino();
    JSONObject json = new JSONObject();

    public boolean confirmaConexao(String porta) {

        boolean confirmacao = false;

        confirmacao = this.comunica.sendCommand(porta, "confirma_conexao");

        return confirmacao;
    }

    public int enviaProg(int linhas, int colunas, JLabel[] lComandos, JLabel[][] lLinhas) throws IOException, FileNotFoundException, ParseException, JSONException {
        int confirma = 0;
        ControleArquivo arquivo = new ControleArquivo();
        config conf;

        conf = arquivo.configuracao();

        if (conf.porta == null) {
            JOptionPane.showMessageDialog(null, "Não há porta selecionada.\n Verifique a configuração de portas.");
            confirma = 3;
        } else {
            confirma = 1;
        }

        return confirma;

    }

    public int varreSaidas(String[] portas) {
        int porta = -1;
        boolean confirma = false;

        for (int i = 0; i < portas.length; i++) {
            confirma = comunica.sendCommand(portas[i], "testePorta");
            if (confirma) {
                porta = i;
            }
        }

        return porta;
    }
}
