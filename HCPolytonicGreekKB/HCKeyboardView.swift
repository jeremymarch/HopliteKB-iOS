//
//  HCKeyboardView.swift
//  HCPolytonicGreekKBapp
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Created by Jeremy March on 9/14/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCKeyboardView: UIView {
    var buttons:[[UIButton]] = []
    var buttonWidth:CGFloat = 0
    /*
    // Only override draw() if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func draw(_ rect: CGRect) {
        // Drawing code
    }
    */
    override func layoutSubviews() {
        super.layoutSubviews()
        
        let viewWidth:CGFloat = self.bounds.width
        let viewHeight:CGFloat = self.bounds.height

        var maxColumns = buttons[0].count
        for a in buttons[0]
        {
            if a.titleLabel?.text == "xxx"
            {
                maxColumns -= 1
            }
        }
        let maxRows = buttons.count
        var buttonHSpacing:CGFloat = 5.0
        let buttonVSpacing:CGFloat = 5.0
        if maxColumns > 9
        {
            buttonHSpacing = 4.0
        }
        
        var c = 0
        var xoffstart:CGFloat = 0
        var xoff:CGFloat = 0
        buttonWidth = 0
        var buttonHeight:CGFloat = 0
        
        for (i, row) in buttons.enumerated()
        {
            c = row.count
            xoffstart = 0
            xoff = 0
            
            if c > 9 && row.last!.titleLabel!.text != "xxx"
            {
                maxColumns = c
            }
            else
            {
                maxColumns = 9
            }
            buttonWidth = (viewWidth - (buttonHSpacing * (CGFloat(maxColumns) + 1.0))) / CGFloat(maxColumns)
            buttonHeight = (viewHeight - (buttonVSpacing * (CGFloat(maxRows) + 1.0))) / CGFloat(maxRows)
            
            if c < maxColumns
            {
                xoffstart = ((buttonWidth + buttonHSpacing) / 2.0) * CGFloat(maxColumns - c) + buttonHSpacing
            }
            else
            {
                xoffstart = buttonHSpacing
            }
            xoff = xoffstart
            var x = false //skip one
            for a in row {
                if a.titleLabel?.text == "enter" || a.titleLabel?.text == "space"
                {
                    if !x
                    {
                        x = true
                        continue
                    }
                    xoff -= (buttonWidth * 2.6) - buttonWidth
                }
            }
            for (j, key) in row.enumerated()
            {
                if key.titleLabel?.text == "xxx"
                {
                    key.isHidden = true
                }
                else
                {
                    key.isHidden = false
                    if i == 3 && j == 7
                    {
                        key.frame = CGRect(x: xoff, y: (CGFloat(i) * (buttonVSpacing + buttonHeight)) + buttonVSpacing, width: buttonWidth * 1.36, height: buttonHeight)
                        xoff += buttonHSpacing + (buttonWidth * 1.36)
                    }
                    else if key.titleLabel?.text == "enter" || key.titleLabel?.text == "space"
                    {
                        key.frame = CGRect(x: xoff, y: (CGFloat(i) * (buttonVSpacing + buttonHeight)) + buttonVSpacing, width: buttonWidth * 2.6, height: buttonHeight)
                        xoff += buttonHSpacing + (buttonWidth * 2.6)
                    }
                    else
                    {
                        //let aa = key as! HCButton
                        var buttonDown = false
                        if let aa = key as? HCButton
                        {
                            if aa.buttonDown
                            {
                                buttonDown = true
                            }
                        }
                        let aa = key as? HCButton
                        
                        if buttonDown && aa!.btype == 0
                        {
                            let width2 = buttonWidth * aa!.buttonDownWidthFactor
                            let height2 = (buttonHeight * aa!.buttonDownHeightFactor) + aa!.buttonTail
                            let x2 = xoff - (((buttonWidth * aa!.buttonDownWidthFactor) - buttonWidth) / 2)
                            let y2 = ((CGFloat(i) * (buttonVSpacing + buttonHeight)) + buttonVSpacing) - height2 + buttonHeight + aa!.buttonTail
                            
                            key.frame = CGRect(x: x2, y: y2, width: width2, height: height2)
                            key.superview?.bringSubview(toFront: key)
                            xoff += (buttonHSpacing + buttonWidth)
                        }
                        else
                        {
                            key.frame = CGRect(x: xoff, y: (CGFloat(i) * (buttonVSpacing + buttonHeight)) + buttonVSpacing, width: buttonWidth, height: buttonHeight)
                            xoff += (buttonHSpacing + buttonWidth)
                        }
                    }
                }
                //key.setNeedsDisplay() //needed for iOS 8.4 when app extension
                //commented out, setting contentMode of button to .redraw achieves same thing.
                //https://stackoverflow.com/questions/13434794/calling-setneedsdisplay-in-layoutsubviews
            }
        }
    }
}
