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
import modelo.Configuracoes;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.simple.parser.ParseException;

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

    @SuppressWarnings("empty-statement")
    public int enviaProg(int linhas, int colunas, JLabel[] lComandos, JLabel[][] lLinhas) throws IOException, FileNotFoundException, ParseException, JSONException, InterruptedException {
        int confirma;

        System.out.println("-----------------INICIO DO ENVIO-----------------");
        controleConfiguracao config = new controleConfiguracao();
        ControleProgramacao contPro = new ControleProgramacao();
        Programacao prog = new Programacao();

        Configuracoes conf;

        prog.status = contPro.iniciaProg();

        conf = config.configuracao();
        System.out.println("Leitura do aquivo de configuração, porta" + conf.getPorta() + " configurada");

        if (conf.porta == null) {
            JOptionPane.showMessageDialog(null, "Não há porta selecionada.\n Verifique a configuração de portas.");
            confirma = 3;
            return confirma;
        }
        if (confirmaConexao(conf.getPorta()) == false) {
            System.out.println("Teste de comunicação, porta configurada não responde");
            JOptionPane.showMessageDialog(null, "A porta " + conf.getPorta() + " não está respondendo.\n Verifique a configuração de portas.");
            confirma = 3;
            return confirma;
        } else {
            System.out.println("Testado comunicação com a porta configurada");
        };

        prog = contPro.organizaComandosEnvio(linhas, colunas, lComandos, lLinhas);
        prog = contPro.organizaPacotes(prog);
        System.out.println("Organizado Json Programação e preparado pacotes para o envio");

        if (comunica.sendCommand(conf.getPorta(), "Ini_envio_prog")) {
            Thread.sleep(500);
            comunica.sendCommand(conf.getPorta(), "" + prog.getPacotes().length);
            System.out.println("Qntd_pacotes_enviar:" + prog.getPacotes().length);
            int i = 0;
            for (String pacote : prog.getPacotes()) {
                Thread.sleep(500);
                if (comunica.sendCommand(conf.getPorta(), pacote) == false) {
                    JOptionPane.showMessageDialog(null, "A porta " + conf.getPorta() + " não está respondendo.\n Verifique a configuração de portas.");
                    confirma = 3;
                    return confirma;
                } else {
                    System.out.println("Pacote " + i + " enviado com sucesso");
                }
                i++;
            }

        } else {

            JOptionPane.showMessageDialog(null, "A porta " + conf.getPorta() + " não está respondendo.\n Verifique a configuração de portas.");
            confirma = 3;
            return confirma;
        };
        confirma = 1;

        System.out.println("-----------------FIM DO ENVIO-----------------\n \n");
        return confirma;

    }

    public int varreSaidas(String[] portas) {
        System.out.println("-----------------INICIO DA VARREDURA------------------");
        int porta = -1;
        boolean confirma = false;

        for (int i = 0; i < portas.length; i++) {
            confirma = comunica.sendCommand(portas[i], "testePorta");
            if (confirma) {
                porta = i;
            }
        }
        System.out.println("-----------------FIM DA VARREDURA----------------- \n \n");
        return porta;
    }
}
