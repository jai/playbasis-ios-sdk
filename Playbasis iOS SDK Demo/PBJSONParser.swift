//
//  PBJSONParser.swift
//  Playbasis iOS SDK Demo
//
//  Created by Jai Govindani on 10/26/14.
//  Copyright (c) 2014 Jai Govindani. All rights reserved.
//

import Foundation

class PBJSONParser {
    
    class func badgesFromData(data: Dictionary<NSObject, AnyObject>) -> [PBBadge]? {
        
        var badgeObjects = [PBBadge]()
        
        if let responseData = data["response"] as? [String: AnyObject] {
            if let badges = responseData["badges"] as? [[String: AnyObject]] {
                
                for (index, value) in enumerate(badges) {
                    let newBadge = PBBadge(badgeData: value)
                    badgeObjects.append(newBadge)
                }
            }
        }
        
        return badgeObjects
    }
}