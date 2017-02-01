//
//  HCAccentButton.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 1/14/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCAccentButton: UIButton {
    /*
    var bgColor:UIColor = .gray
    var bgDownColor:UIColor = .black
    var textColor:UIColor = .white
    var textDownColor:UIColor = .white
    */
    var bgColor = HopliteConstants.accentBGColor
    var textColor = HopliteConstants.accentTextColor
    var bgDownColor = HopliteConstants.accentBGColorDown
    var textDownColor = HopliteConstants.accentTextColorDown
    
    var btype: Int? = nil
    
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
    
    func touchUpInside(sender: UIButton!) {
        
        backgroundColor = bgColor
        setTitleColor(textColor, for: [])
        //setNeedsDisplay()
    }
    
    func touchUpOutside(sender: UIButton!) {
        
        backgroundColor = bgColor
        setTitleColor(textColor, for: [])
        //setNeedsDisplay()
    }
    
    func touchDown(sender: UIButton!) {
        
        backgroundColor = bgDownColor
        setTitleColor(textDownColor, for: [])
        setNeedsDisplay()
    }
}
