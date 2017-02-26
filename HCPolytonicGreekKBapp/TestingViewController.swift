//
//  TestingViewController.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 2/26/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class TestingViewController: UIViewController, UITextViewDelegate {
    @IBOutlet var textView:UITextView?
    @IBOutlet var HexLabel:UILabel?
    @IBOutlet var modeLabel:UILabel?
    var kb:KeyboardViewController? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        kb = KeyboardViewController() //kb needs to be member variable, can't be local to just this function
        kb?.appExt = false
        
        textView!.inputView = kb?.view
        textView!.delegate = self
        
        let defaults = UserDefaults(suiteName: "group.com.philolog.hoplitekeyboard")
        if defaults != nil
        {
            let m = defaults?.object(forKey: "UnicodeAccents")
            if m != nil
            {
                let n:Int32 = m as! Int32
                if n >= 0 && n <= 2
                {
                    if n == UnicodeMode.PreComposedNoPUA.rawValue
                    {
                        modeLabel?.text = "Mode: Precomposed"
                    }
                    else if n == UnicodeMode.PreComposedPUA.rawValue
                    {
                        modeLabel?.text = "Mode: Precomposed with PUA"
                    }
                    else if n == UnicodeMode.CombiningOnly.rawValue
                    {
                        modeLabel?.text = "Mode: Combining Only"
                    }
                }
            }
 
        }
        modeLabel?.sizeToFit()

        // Do any additional setup after loading the view.
    }
    
    func textViewDidChange(_ textView: UITextView) { //Handle the text changes here
        /*
        let COMBINING_GRAVE =            0x0300
        let COMBINING_ACUTE =            0x0301
        let COMBINING_CIRCUMFLEX =       0x0342//0x0302
        let COMBINING_MACRON =           0x0304
        let COMBINING_DIAERESIS =        0x0308
        let COMBINING_SMOOTH_BREATHING = 0x0313
        let COMBINING_ROUGH_BREATHING =  0x0314
        let COMBINING_IOTA_SUBSCRIPT =   0x0345
        let EM_DASH =                    0x2014
        let LEFT_PARENTHESIS =           0x0028
        let RIGHT_PARENTHESIS =          0x0029
        let SPACE =                      0x0020
        let EN_DASH =                    0x2013
        let HYPHEN =                     0x2010
        let COMMA =                      0x002C
        
        let combiningChars = [COMBINING_GRAVE,COMBINING_ACUTE,COMBINING_CIRCUMFLEX,COMBINING_MACRON,COMBINING_DIAERESIS,COMBINING_SMOOTH_BREATHING,COMBINING_ROUGH_BREATHING,COMBINING_IOTA_SUBSCRIPT]
        */
        
        let s = textView.text
        HexLabel?.text = "Unicode Code Points:\n" + textToCodePoints(text: s!, separator: " - ")
        HexLabel?.sizeToFit()
        
        /*
        var topCorrect:CGFloat = (textView.bounds.size.height - textView.contentSize.height) / 2.0
        topCorrect = ( topCorrect < 0.0 ? 0.0 : topCorrect )
        textView.contentOffset = CGPoint(x: 0, y: topCorrect)
        */
    }

    func textToCodePoints(text:String, separator:String) -> String
    {
        var ns:String = ""
        for a in (text.unicodeScalars)
        {
            //NSLog(String(a.value, radix:16))
            //ns = ns + String(a.value, radix:16) + " "
            ns = ns + String(format: "%04X", a.value) + separator
        }
        let endIndex = ns.index(ns.endIndex, offsetBy: -separator.characters.count, limitedBy: ns.startIndex)
        if endIndex != nil
        {
            return ns.substring(to: endIndex!)
        }
        else
        {
            return ns
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        //[[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
        self.navigationController?.setNavigationBarHidden(false, animated: true)
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
