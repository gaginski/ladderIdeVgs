/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.JLabel;
import modelo.Programacao;
import modelo.config;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.simple.parser.ParseException;

/**
 *
 * @author Vitor
 */
public class ControleProgramacao {

    Programacao prog = new Programacao();
    ControleArquivo controleArquivo = new ControleArquivo();
    String stringComandos = "";

    public String organizaComandosExibicao(int linhas, int colunas, JLabel[] lComandos, JLabel[][] lLinhas) throws JSONException, IOException, UnknownHostException, FileNotFoundException, ParseException {

        organizaComandosEnvio(linhas, colunas, lComandos, lLinhas);

        return stringComandos;
    }

    public Programacao organizaComandosEnvio(int linhas, int colunas, JLabel[] lComandos, JLabel[][] lLinhas) throws JSONException, IOException, UnknownHostException, FileNotFoundException, ParseException {
        // declara variveis 
        int[][][] matrizComandos = new int[linhas][colunas][5];
        JSONObject jsonEntrada = new JSONObject();
        JSONObject jsonSaida = new JSONObject();
        JSONObject jsonAux = new JSONObject();
        JSONObject jsonComandos = new JSONObject();
        String entradas = "";
        String saidas = "";

        // captura status no objeto prog
        prog.status = iniciaProg();

        //percorre todos as labels comparando o icone com os comandos, salvando na matriz os as informações de comandos setados
        for (int i = 0; i < linhas; i++) {
            for (int c = 0; c < colunas; c++) {
                for (int a = 0; a < lComandos.length; a++) {
                    if (lLinhas[i][c].getIcon().equals(lComandos[a].getIcon())) {
                        matrizComandos[i][c][0] = 1; // confirmaConteudo
                        matrizComandos[i][c][1] = i; // Linha
                        matrizComandos[i][c][2] = c; // Coluna
                        matrizComandos[i][c][3] = a; // Comando
                        matrizComandos[i][c][4] = Integer.parseInt(lLinhas[i][c].getText()); // Porta

                    }
                }
            }
        }

        // percorre toda a matriz int  preenchida, gerando o json
        for (int i = 0; i < linhas; i++) {
            int contE = 0;
            int contS = 0;
            stringComandos = stringComandos + ("Linha_" + i + ": {");
            entradas = "\n   Entrada{ ";
            saidas = "\n   Saídas{ ";
            for (int c = 0; c < colunas; c++) {
                if (matrizComandos[i][c][0] == 1) {

                    switch (matrizComandos[i][c][3]) {
                        case (0):
                        case (1):
                        case (2):
                        case (3):
                            jsonEntrada.put("Cm" + contE, matrizComandos[i][c][3] + ", " + matrizComandos[i][c][4]);
                            entradas = entradas + "\n       Comando:" + matrizComandos[i][c][3]
                                    + ", Porta:" + matrizComandos[i][c][4];
                            contE++;
                            break;
                        case (4):
                        case (5):
                        case (6):
                        case (7):
                            jsonSaida.put("Cm" + contS, matrizComandos[i][c][3] + ", " + matrizComandos[i][c][4]);
                            saidas = saidas + "\n       Comando:" + matrizComandos[i][c][3]
                                    + ", Porta:" + matrizComandos[i][c][4];
                            contS++;
                            break;
                        default:
                            break;

                    }

                }
            }
            entradas = entradas + "}";
            saidas = saidas + "}";
            stringComandos = stringComandos + entradas + saidas + "\n   }\n";
            jsonAux.put("In", jsonEntrada);
            jsonAux.put("Out", jsonSaida);
            jsonComandos.put("Ln" + i, jsonAux);
            jsonAux = new JSONObject();
            jsonEntrada = new JSONObject();
            jsonSaida = new JSONObject();

        }

        prog.parametros = jsonComandos;
        //System.out.println(jsonComandos);
        organizaPacotes(prog);

        return prog;
    }

    public Programacao organizaPacotes(Programacao p) {

        String aux = null;
        int cont, tamanhoVetor = p.parametros.toString().length();

        aux = p.parametros.toString();

        cont = (int) Math.floor(tamanhoVetor / 220) + 1;
        
        String[] pacotes = new String[cont];
        
        for (int i = 0; i < cont; i++) {
            if (i == cont - 1) {
                pacotes[i] = aux.substring(i * 220, aux.length());
            } else {
                pacotes[i] = aux.substring(i * 220, (i * 220) + 220);
            }
        }
        
        p.pacotes = pacotes;
        
        return p;
    }

    private JSONObject iniciaProg() throws JSONException, UnknownHostException, IOException, FileNotFoundException, ParseException {
        JSONObject status = new JSONObject();
        DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        Date date = new Date();
        config c = new config();
        c = controleArquivo.configuracao();

        status.put("DataHoraCarregamento", dateFormat.format(date));
        status.put("Pc_Carregou", InetAddress.getLocalHost().getHostName());
        status.put("IP_carregou", InetAddress.getLocalHost().getAddress());
        status.put("Porta", c.porta);

        return status;

    }

}
