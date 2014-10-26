//
//  PBBadge.swift
//  Playbasis iOS SDK Demo
//
//  Created by Jai Govindani on 10/26/14.
//  Copyright (c) 2014 Jai Govindani. All rights reserved.
//

import Foundation

class PBBadge {
    var badgeID : String
    var badgeImageURL : NSURL?
    var badgeName : String
    var badgeDescription : String?
    var badgeHint : String?
    
     init (badgeData: Dictionary<String, AnyObject>) {
        badgeID = badgeData["badge_id"] as String
        badgeName = badgeData["name"] as String
    }
}