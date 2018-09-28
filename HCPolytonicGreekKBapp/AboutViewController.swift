//
//  AboutViewController.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 2/24/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//


import UIKit

class AboutViewController: UIViewController {
    @IBOutlet var label:UILabel?
    override func viewDidLoad() {
        super.viewDidLoad()
        
        label?.sizeToFit()
        
        let s = "USE: \n• Type the letter first, then add diacritics.\n• Diacritics can be added in any order.\n• Pressing the diacritic again will toggle it on or off.\n• Contrasting diacritics replace each other.\n• Press caps lock to see the diaeresis and breve keys.\n•Typing a diacritic key after a letter which cannot receive the diacritic will type a spacing diacritic.\n\nSETTINGS: \n• Precomposed will use precomposed unicode characters when possible, falling back to combining diacritics if a precomposed character doesn't exist.\n• Precomposed with PUA is like the above, but will also use precomposed characters from the Private Use Area when possible.  This is only supported by certain fonts and is not standard unicode.\n• Combining Only uses only combining diacritics.  This is only supported by certain fonts."
        
        var fsize:CGFloat = 18.0
        //for iphone 5s and narrower
        if UIScreen.main.nativeBounds.width < 641
        {
            fsize = 14.0
        }
        
        let font = UIFont(name: "HelveticaNeue", size: fsize)!
        let s2 = NSMutableAttributedString(string: s, attributes: [NSAttributedString.Key.font: font])
        
        let italicsFont = UIFont(name: "HelveticaNeue-BoldItalic", size: fsize)!
        
        //s2.addAttribute(NSFontAttributeName, value: italicsFont, range: NSRange(location: 335, length:11))
        
        s2.addAttribute(NSAttributedString.Key.font, value: italicsFont, range: NSRange(location: 368, length:11))
        s2.addAttribute(NSAttributedString.Key.font, value: italicsFont, range: NSRange(location: 515, length:21))
        s2.addAttribute(NSAttributedString.Key.font, value: italicsFont, range: NSRange(location: 708, length:16))
        
        label?.attributedText = s2
    }
    
    override func viewWillAppear(_ animated: Bool) {
        //[[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
        self.navigationController?.setNavigationBarHidden(false, animated: true)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
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
