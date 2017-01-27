//
//  HCbutton.swift
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 1/14/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

import UIKit

class HCButton: UIButton {

    var btype: Int? = nil
    let bgColor:UIColor = .white
    let bgDownColor:UIColor = .black
    let textColor:UIColor = .black
    let textDownColor:UIColor = .white
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
        if btype == 1
        {
            backgroundColor = .white
        }
        self.addTarget(self, action: #selector(touchUpInside(sender:)), for: .touchUpInside)
        self.addTarget(self, action: #selector(touchUpOutside(sender:)), for: .touchUpOutside)
        self.addTarget(self, action: #selector(touchDown(sender:)), for: .touchDown)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func touchUpInside(sender: UIButton!) {
        
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
    
    func touchUpOutside(sender: UIButton!) {
        
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
    
    func touchDown(sender: UIButton!) {
        
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
