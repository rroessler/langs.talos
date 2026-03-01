/// Node Modules
import * as fs from 'node:fs';

/// Vendor Modules
import * as YAML from 'yaml';
import * as shiki from 'shiki';

/// Library Modules
import { Assets } from '../assets';
import { Product } from '../product';

/** Handles getting the underlying grammar. */
export type Grammar = shiki.LanguageInput;
export async function Grammar(): Promise<Grammar> {
    return fs.promises
        .readFile(Assets.syntaxes('talos.tmLanguage.yaml'), 'utf-8')
        .then(YAML.parse)
        .catch(() => ({
            patterns: [],
            repository: {},
            name: Product.identifier,
            scopeName: `source${Product.extension}`,
        }));
}
