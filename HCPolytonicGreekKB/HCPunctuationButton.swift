//
//  HCPunctuationButton.swift
//  HCPolytonicGreekKBapp
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Created by Jeremy March on 1/30/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCPunctuationButton: UIButton {
        
        var btype: Int? = nil
    /*
    var bgColor:UIColor = .white
        var bgDownColor:UIColor = .black
        var textColor:UIColor = .black
        var textDownColor:UIColor = .white
    */
    var bgColor = HopliteConstants.punctuationBGColor
    var textColor = HopliteConstants.punctuationTextColor
    var bgDownColor = HopliteConstants.punctuationBGColorDown
    var textDownColor = HopliteConstants.punctuationTextColorDown
    
        let blueColor:UIColor = UIColor.init(red: 0/255.0, green: 122/255.0, blue: 255/255.0, alpha: 1.0)
        /*
         // Only override draw() if you perform custom drawing.
         // An empty implementation adversely affects performance during animation.
         override func draw(_ rect: CGRect) {
         // Drawing code
         }
         */
        
        required init(buttonType: Int = 0) {
            // set myValue before super.init is called
            self.btype = buttonType
            
            super.init(frame: .zero)
            
            // set other operations after super.init, if required
            
            backgroundColor = bgColor
            setTitleColor(textColor, for: [])
            
            self.addTarget(self, action: #selector(touchUpInside(sender:)), for: .touchUpInside)
            self.addTarget(self, action: #selector(touchUpOutside(sender:)), for: .touchUpOutside)
            self.addTarget(self, action: #selector(touchDown(sender:)), for: .touchDown)
        }
        
        required init?(coder aDecoder: NSCoder) {
            fatalError("init(coder:) has not been implemented")
        }
        
        @objc func touchUpInside(sender: UIButton!) {
            
            if self.titleLabel?.text == "enter"
            {
                setTitleColor(.white, for: [])
                backgroundColor = blueColor
            }
            else if self.titleLabel?.text == "space"
            {
                setTitleColor(.gray, for: [])
                backgroundColor = .white
            }
            else
            {
                backgroundColor = bgColor
                setTitleColor(textColor, for: [])
                //setNeedsDisplay()
            }
        }
        
        @objc func touchUpOutside(sender: UIButton!) {
            
            if self.titleLabel?.text == "enter"
            {
                setTitleColor(.white, for: [])
                backgroundColor = blueColor
            }
            else if self.titleLabel?.text == "space"
            {
                setTitleColor(.gray, for: [])
                backgroundColor = .white
            }
            else
            {
                backgroundColor = bgColor
                setTitleColor(textColor, for: [])
                //setNeedsDisplay()
            }
        }
        
        @objc func touchDown(sender: UIButton!) {
            
            if self.titleLabel?.text == "enter"
            {
                setTitleColor(blueColor, for: [])
                backgroundColor = .white
            }
            else if self.titleLabel?.text == "space"
            {
                setTitleColor(.white, for: [])
                backgroundColor = .black
            }
            else
            {
                backgroundColor = bgDownColor
                setTitleColor(textDownColor, for: [])
            }
            //setNeedsDisplay()
        }
        
}
